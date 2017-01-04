from django.http import HttpResponse
from django.core.exceptions import ObjectDoesNotExist

import json

from .models import Member, Team


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
    pass


def register_user(request, teamname, username):
    pass


def get_team(request, teamname):
    pass


def get_team_members(request, teamname):
    pass


def get_team_record(request, teamname):
    pass


def get_all_teams(request):
    pass


def propose_token(request):
    pass
