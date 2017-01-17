from django.http import HttpResponse
from django.core.exceptions import ObjectDoesNotExist

import json

from .models import Member, Team, Step, Attempt
from .encodedstate import EncodedState, ChecksumError


def forge_json_response(payload, code=200):
    if type(payload)==str:
        try:
            json.loads(payload)
            jsonstr = payload
        except ValueError:
            raise(ValueError, 'Payload is not a valid json string')
    else:
        jsonstr = json.dumps(payload)
    return HttpResponse(jsonstr, status=code, content_type='application/json')


def get_user(request, username):
    """ Return the teams associated to the user "username".  """

    try:
        user = Member.objects.get(pseudo=username)
    except ObjectDoesNotExist:
        payload = {
            'status': 'unknown user',
            'command': 'get_user',
            'result': []
        }
        return forge_json_response(payload, code=404)

    payload = {
        'status': 'user found',
        'command': 'get_user',
        'result': [user.asdict()]
    }
    return forge_json_response(payload)


def get_all_users(request):
    """Return the list of all users"""
    users = Member.objects.all()
    payload = {
        'command': 'get_all_users',
        'result': [u.asdict() for u in users]
    }
    if len(users)==0:
        payload['status'] = 'no user found'
    else:
        payload['status'] = 'users found'
    return forge_json_response(payload)


def register_user(request, teamname, username):
    """Register user 'username' into team 'teamname', creating both if needed.  """

    payload = {'command': 'register_user'}

    # First, check if the member is already registered
    try:
        user = Member.objects.get(pseudo=username)
        payload['result'] = user.asdict()
        code = 200

        if user.team.name==teamname:
            payload['status'] = 'user already in team %s'%(user.team.name,)
        else:
            payload['status'] = 'user already in another team (%s)'%(user.team.name,)
            code = 409

        return forge_json_response(payload, code=code)

    except ObjectDoesNotExist:
        # the user does not exist, start creating it
        user = Member(pseudo=username)

    # then, retrieve the team object if it exists or create it
    try:
        team = Team.objects.get(name=teamname)
        new_team = False
    except ObjectDoesNotExist:
        try:
            team = Team.objects.create(name=teamname)
            new_team = True
        except:  # at this point the only way to fail is a DB issue
            code = 500
            payload['result'] = []
            payload['status'] = 'failed to add team'
            return forge_json_response(payload, code=500)

    user.team = team
    try:
        user.save()
        payload['result'] = user.asdict()
        if new_team:
            payload['status'] = 'user and team created'
        else:
            payload['status'] = 'user created'
        return forge_json_response(payload)
    except:  # at this point the only way to fail is a DB issue
        code = 500
        payload['result'] = []
        payload['status'] = 'failed to add user'
        return forge_json_response(payload, code=500)


def get_team(request, teamid):
    """Returns a complete Team object (with associated primary users)"""

    try:
        team = Team.objects.get(laumio=teamid)
    except ObjectDoesNotExist:
        payload = {
            'status': 'unknown team',
            'command': 'get_team',
            'result': []
        }
        return forge_json_response(payload, code=404)

    payload = {
        'status': 'team found',
        'command': 'get_team',
        'result': [team.asdict(members=True)]
    }
    return forge_json_response(payload)


def get_team_members(request, teamid):
    """Returns a list of Team teamid's members"""

    payload = {'command': 'get_team_members'}
    try:
        team = Team.objects.get(laumio=teamid)
    except ObjectDoesNotExist:
        payload = {
            'status': 'unknown team',
            'command': 'get_team_members',
            'result': []
        }
        return forge_json_response(payload, code=404)

    usercount = team.member_set.filter(primary=True).count()
    if usercount:
        payload['result'] = [_.asdict(team=False) for _ in team.member_set.filter(primary=True)]
        payload['status'] = '%d member(s) in team'%(usercount,)
    else:
        payload['result'] = []
        payload['status'] = 'no member in team'
    return forge_json_response(payload)


def get_team_record(request, teamid):
    """Get a full log of all actions from a team"""

    payload = {'command': 'get_team_record'}
    try:
        team = Team.objects.get(laumio=teamid)
    except ObjectDoesNotExist:
        payload = {
            'status': 'unknown team',
            'command': 'get_team_record',
            'result': []
        }
        return forge_json_response(payload, code=404)

    record = team.attempt_set.order_by('-timestamp')
    count = record.count()
    if count:
        payload['status'] = '%d event(s) found'%(count,)
    else:
        payload['status'] = 'no event found'

    payload['result'] = [_.asdict() for _ in record]
    return forge_json_response(payload)


def get_all_teams(request):
    """Return the list of all teams"""
    teams = Team.objects.all()
    payload = {
        'command': 'get_all_teams',
        'result': [t.asdict(members=False) for t in teams]
    }
    if len(teams)==0:
        payload['status'] = 'no team found'
    else:
        payload['status'] = 'teams found'
    return HttpResponse(json.dumps(payload), content_type='application/json')


def propose_token(request, username, token):
    """Get data out of the token, log it, process it."""

    # if token checksum fails to pass, do not process
    try:
        tokenstate = EncodedState().from_string(token)
        if not tokenstate:
            return forge_json_response({
                'status': 'invalid token',
                'command': 'propose_token',
                'result': [token]
            })
    except ChecksumError:
        return forge_json_response({
            'status': 'incorrect checksum',
            'command': 'propose_token',
            'result': []
        })

    if tokenstate['direction']!=0:
        return forge_json_response({
            'status': 'wrong direction',
            'command': 'propose_token',
            'result': []
        })


    submitter = Member.objects.get(pseudo=username)
    team = submitter.team

    # if username's team has no laumio field set, set the laumio id
    # in team's record
    if team.laumio=='':
        team.laumio = '%04x'%(tokenstate['id'],)
        team.save()
    else:
        if team.laumio!='%04x'%(tokenstate['id'],):
            try:
                token_team = Team.objects.get(laumio='%04x'%(tokenstate['id'],))
            except ObjectDoesNotExist:
                return forge_json_response({
                    'status': 'submitter not part of team',
                    'command': 'propose_token',
                    'result': {
                        'submitter_team': team.name,
                        'token_team': None
                    }
                })
            return forge_json_response({
                'status': 'submitter not part of team',
                'command': 'propose_token',
                'result': {
                    'submitter_team': team.name,
                    'token_team': token_team.name
                }
            })


    previous_attempts = Attempt.objects.filter(team=team).order_by('-timestamp')
    if previous_attempts.count()!=0:
        previous_token = EncodedState().from_string(previous_attempts[0].token_out)

        fields = ['riddle', 'id', 'riddleparams', 'sentence', 'animation', 'animparams']
        modified_fields = [f for f in fields if previous_token.D.get(f)!=tokenstate.D.get(f)]
        if modified_fields:
            return forge_json_response({
                'status': 'illegal token',
                'command': 'propose_token',
                'result': {
                    'modified_fields': modified_fields,
                }
            })
    else: # Guard, you never know
        team.step = Step.objects.get(index=0)
        team.challenge = team.step.challenge
        team.jail = False

    attempt = Attempt(
        step=team.step,
        challenge=team.challenge,
        jail=team.jail,
        team=team,
        submitter=submitter,
        token_in=token,
        token_out='',  # so we can save it
        faults=tokenstate['faults'],
    )
    attempt.save()

    if tokenstate['final_success']:
        if team.jail:
            attempt.points = 0
            team.jail = False
        else:
            attempt.points = +2**team.step.index
            try:
                next_step = Step.objects.get(index=team.step.index+1)
                team.step = next_step
            except ObjectDoesNotExist:
                return forge_json_response({
                    'status': 'Habemus victorem',
                    'command': 'propose_token',
                    'result': '~o~'
                })
        team.challenge = team.step.challenge
    else:
        attempt.points = -team.step.index**2
        if team.jail:
            attempt.points *= 2
        else:
            team.jail = True

        if team.step.jails.count()!=0:
            team.challenge = team.step.jails.order_by('?')[0]
        else:
            team.challenge = team.step.challenge

    token_out = EncodedState({
        'id': team.laumio,
        'riddleparams': team.challenge.params,
        'faults': 0,
        'animation': team.step.animation.index,
        'sentence': 0,
        'final_success': 0,
        'direction': 1,
        'riddle': team.challenge.index,
        'animparams': team.step.animation.params
    })
    attempt.token_out = token_out
    attempt.save()

    team.score += attempt.points
    team.save()

    return forge_json_response({
        'status': 'valid token',
        'command': 'propose_token',
        'result': {
            'next': {
                'token': str(token_out),
                'next': team.challenge.name,
                'type': 'jail' if team.jail else 'riddle'
            }
        }
    })
