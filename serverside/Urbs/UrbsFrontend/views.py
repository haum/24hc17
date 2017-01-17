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


def get_team(request, teamname):
    """Returns a complete Team object (with associated primary users)"""

    try:
        team = Team.objects.get(name=teamname)
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


def get_team_members(request, teamname):
    """Returns a list of Team teamname's members"""

    payload = {'command': 'get_team_members'}
    try:
        team = Team.objects.get(name=teamname)
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


def propose_token(request):
    pass
