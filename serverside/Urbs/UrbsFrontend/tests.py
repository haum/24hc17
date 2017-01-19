from django.test import TestCase
from django.urls import reverse

import json
import copy

from .models import Team, Member, Challenge, Attempt, Step, Animation
from .encodedstate import EncodedState
from .scoring import Scorer as S


class UserViewTests(TestCase):
    """Test the 2 views related to users"""

    @classmethod
    def setUpTestData(cls):
        cls.team = Team.objects.create(
            name="Team",
            location="Moon",
            score=42
        )

    def test_unknown_user(self):
        """Appropriate message if the required user is not in the database"""

        Member.objects.create(pseudo='user', team=self.team)
        response = self.client.get(reverse('user#get_user', args=['anotheruser']))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'unknown user',
                'command': 'get_user',
                'result': []
            }
        )

    def test_no_user(self):
        """Appropriate message if there is no user in the database"""

        response = self.client.get(reverse('user#get_user', args=['anotheruser']))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'unknown user',
                'command': 'get_user',
                'result': []
            }
        )

    def test_full_list_no_user(self):
        """Appropriate message if there is no user in the database"""

        response = self.client.get(reverse('user#all'))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'no user found',
                'command': 'get_all_users',
                'result': []
            }
        )

    def test_full_list_with_user(self):
        """Appropriate message if there is no user in the database"""

        exppayload_result = []
        for i in range(9):
            u = Member.objects.create(pseudo='user%d'%(i,), team=self.team)
            exppayload_result.append(u.asdict())
        response = self.client.get(reverse('user#all'))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'users found',
                'command': 'get_all_users',
                'result': exppayload_result
            }
        )


class RegisterViewTests(TestCase):
    """Test if the registering process goes right"""

    def test_full_registration(self):
        """
        The /team/<teamname>/adduser/<username> is called
        with neither team or user existing beforehand.
        """

        self.maxDiff = None

        response = self.client.get(reverse('team#register_user', args=['Team1', 'User1']))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'user and team created',
                'command': 'register_user',
                'result': {
                    'pseudo': 'User1',
                    'primary': True,
                    'team': {
                        'name': 'Team1',
                        'location': '',
                        'score': 0,
                        'laumio': ''
                    }
                }
            }
        )
        u1 = Member.objects.get(pseudo='User1')
        t1 = Team.objects.get(name='Team1')
        self.assertEqual(str(u1), 'User1 (Team1)')
        self.assertEqual(t1.score, 0)
        self.assertEqual(t1, u1.team)

    def test_partial_registration(self):
        """
        The /team/<teamname>/adduser/<username> is called
        with team already registered.
        """

        t1 = Team.objects.create(name='Team1')
        response = self.client.get(reverse('team#register_user', args=['Team1', 'User1']))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'user created',
                'command': 'register_user',
                'result': {
                    'pseudo': 'User1',
                    'primary': True,
                    'team': t1.asdict()
                }
            }
        )

        u1 = Member.objects.get(pseudo='User1')
        self.assertEqual(str(u1), 'User1 (Team1)')
        self.assertEqual(Team.objects.count(), 1)
        self.assertEqual(t1, u1.team)

    def test_already_registered(self):
        """
        The /team/<teamname>/adduser/<username> is called
        with team and user already registered (user being linked to team).
        """

        t1 = Team.objects.create(name='Team1')
        u1 = Member.objects.create(pseudo='User1', team=t1)
        response = self.client.get(reverse('team#register_user', args=[t1.name, u1.pseudo]))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'user already in team %s'%(t1.name,),
                'command': 'register_user',
                'result': u1.asdict()
            }
        )

        self.assertEqual(Member.objects.count(), 1)
        self.assertEqual(Team.objects.count(), 1)

    def test_conflicting_registration(self):
        """
        The /team/<teamname>/adduser/<username> is called
        with user already registered in another team.
        """

        t1 = Team.objects.create(name='Team1')
        u1 = Member.objects.create(pseudo='User1', team=t1)
        response = self.client.get(reverse('team#register_user', args=['Another_Team', u1.pseudo]))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'user already in another team (%s)'%(t1.name,),
                'command': 'register_user',
                'result': u1.asdict()
            }
        )

        self.assertEqual(response.status_code, 409)
        self.assertEqual(Member.objects.count(), 1)
        self.assertEqual(Team.objects.count(), 1)


class TeamViewTests(TestCase):
    """Tests the Team view"""

    @classmethod
    def setUpTestData(cls):
        cls.t1 = Team.objects.create(
            name='Harkonnen',
            location='Giedi Prime',
            score=3,
            laumio='0001'
        )

        cls.t2 = Team.objects.create(
            name='Atreides',
            location='Arakis',
            score=42,
            laumio='0002'
        )
        cls.u1 = Member.objects.create(pseudo='Leto', team=cls.t2)
        cls.u2 = Member.objects.create(pseudo='Paul', team=cls.t2)

    def test_without_users(self):
        """Test the output of the view if the team has no user"""
        response = self.client.get(reverse('team#get_team', args=[self.t1.laumio]))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'command': 'get_team',
                'status': 'team found',
                'result': [self.t1.asdict(members=True)]
            }
        )

    def test_with_users(self):
        """Test the output of the view if the team has users"""
        response = self.client.get(reverse('team#get_team', args=[self.t2.laumio]))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'command': 'get_team',
                'status': 'team found',
                'result': [self.t2.asdict(members=True)]
            }
        )

    def test_with_unknown_team(self):
        """Test the output of the view if the team doesn't exist"""
        response = self.client.get(reverse('team#get_team', args=['0FFF']))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'unknown team',
                'command': 'get_team',
                'result': []
            }
        )


class TeamMembersViewTests(TestCase):
    """Tests the Team members view"""

    @classmethod
    def setUpTestData(cls):
        cls.t1 = Team.objects.create(
            name='Harkonnen',
            location='Giedi Prime',
            score=3,
            laumio='0001'
        )

        cls.t2 = Team.objects.create(
            name='Atreides',
            location='Arakis',
            score=42,
            laumio='0002'
        )
        cls.u1 = Member.objects.create(pseudo='Leto', team=cls.t2)
        cls.u2 = Member.objects.create(pseudo='Paul', team=cls.t2)

    def test_without_users(self):
        """Test the output of the view if the team has no user"""
        response = self.client.get(reverse('team#members', args=[self.t1.laumio]))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'command': 'get_team_members',
                'status': 'no member in team',
                'result': []
            }
        )

    def test_with_users(self):
        """Test the output of the view if the team has users"""
        response = self.client.get(reverse('team#members', args=[self.t2.laumio]))
        usercount = self.t2.member_set.filter(primary=True).count()
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'command': 'get_team_members',
                'status': '%d member(s) in team'%(usercount,),
                'result': [_.asdict(team=False) for _ in self.t2.member_set.filter(primary=True)]
            }
        )

    def test_with_unknown_team(self):
        """Test the output of the view if the team doesn't exist"""
        response = self.client.get(reverse('team#members', args=['0FFF']))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'command': 'get_team_members',
                'status': 'unknown team',
                'result': []
            }
        )


class TeamAllViewTests(TestCase):
    """Test the teams listing view"""

    def test_full_list_no_team(self):
        """Appropriate message if there is no team in the database"""

        response = self.client.get(reverse('team#all'))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'no team found',
                'command': 'get_all_teams',
                'result': []
            }
        )

    def test_full_list_with_user(self):
        """Appropriate message if there is no user in the database"""

        t1 = Team.objects.create(
            name='Harkonnen',
            location='Giedi Prime',
            score=3,
            laumio='0001'
        )

        t2 = Team.objects.create(
            name='Atreides',
            location='Arakis',
            score=42
        )  # no laumio number defined (on purpose)
        Member.objects.create(pseudo='Leto', team=t2)
        Member.objects.create(pseudo='Paul', team=t2)

        response = self.client.get(reverse('team#all'))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'teams found',
                'command': 'get_all_teams',
                'result': [t1.asdict(members=False), t2.asdict(members=False)]
            }
        )


class TeamRecordViewTests(TestCase):
    """Test the team record view"""

    def test_no_team(self):
        """The view must return a 404 for all teams when no team is registered"""

        response = self.client.get(reverse('team#record', args=['00FF']))
        self.assertEqual(response.status_code, 404)
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'unknown team',
                'command': 'get_team_record',
                'result': []
            }
        )

    def test_unknown_team(self):
        """The view must return a 404 when the team doesn't exist"""

        Team.objects.create(
            name='Atreides',
            location='Arakis',
            score=42,
            laumio='000A'
        )
        response = self.client.get(reverse('team#record', args=['0FFF']))
        self.assertEqual(response.status_code, 404)
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'unknown team',
                'command': 'get_team_record',
                'result': []
            }
        )

    def test_empty_record(self):
        """The view must return the empty list of events"""

        Team.objects.create(
            name='Atreides',
            location='Arakis',
            score=42,
            laumio='0001'
        )
        response = self.client.get(reverse('team#record', args=['0001']))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'no event found',
                'command': 'get_team_record',
                'result': []
            }
        )

    def test_with_record(self):
        """The view must return the list of events"""

        self.maxDiff = None

        t = Team.objects.create(
            name='Atreides',
            location='Arakis',
            score=42,
            laumio='0001'
        )
        anim = Animation.objects.create(name='anim')
        s = Step.objects.create(challenge=Challenge.objects.create(
                name='FremenTest',
                description='Ride the sandworm',
                index=1
            ),
            index=1,
            animation=anim
        )
        u = Member.objects.create(pseudo='Paul', team=t)
        token = EncodedState({
            'id': '0000',
            'riddleparams': 0,
            'faults': 0,
            'animation': 0,
            'sentence': 0,
            'final_success': 0,
            'direction': 0,
            'riddle': 1,
            'animparams': 0,
        })
        a = Attempt.objects.create(
            step=s,
            challenge=s.challenge,
            jail=False,
            team=t,
            submitter=u,
            token_in=str(token),
            token_out=str(token),
            faults=7,
            points=10
        )
        response = self.client.get(reverse('team#record', args=['0001']))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': '1 event(s) found',
                'command': 'get_team_record',
                'result': [a.asdict()]
            }
        )


class ProposeTokenTests(TestCase):
    """Test the verification of the tokens"""

    @classmethod
    def setUpTestData(cls):
        """ Set up two teams, two steps """

        cls.t1 = Team.objects.create(
            name="Atreides",
            laumio='0001'
        )
        cls.t1u1 = Member.objects.create(
            pseudo='Leto',
            team=cls.t1
        )
        cls.t1u2 = Member.objects.create(
            pseudo='Paul',
            team=cls.t1
        )
        cls.t2 = Team.objects.create(
            name="Harkonnen",
            laumio='0002'
        )
        cls.t2u1 = Member.objects.create(
            pseudo='Vladimir',
            team=cls.t2
        )
        cls.t2u2 = Member.objects.create(
            pseudo='Rautha',
            team=cls.t2
        )
        cls.anim = Animation.objects.create(
            name='Anim'
        )
        cls.c0 = Challenge.objects.create(
            name='Challenge0',
            description='Second Challenge',
            index=0
        )
        cls.c1 = Challenge.objects.create(
            name='Challenge1',
            description='First Challenge',
            index=1
        )
        cls.c2 = Challenge.objects.create(
            name='Challenge2',
            description='Second Challenge',
            index=2
        )
        cls.j1 = Challenge.objects.create(
            name='Jail1',
            is_jail=True,
            description='First Jail',
            index=3
        )
        cls.j2 = Challenge.objects.create(
            name='Jail2',
            is_jail=True,
            description='Second Jail',
            index=4
        )
        cls.s0 = Step.objects.create(
            index=0,
            challenge=cls.c0,
            animation=cls.anim
        )
        cls.s1 = Step.objects.create(
            index=1,
            challenge=cls.c1,
            animation=cls.anim
        )
        cls.s1.jails=[cls.j1]
        cls.s1.save()
        cls.s2 = Step.objects.create(
            index=2,
            challenge=cls.c2,
            animation=cls.anim
        )
        cls.s2.jails=[cls.j2, cls.c1]
        cls.s2.save()

        cls.basetoken = EncodedState({
            'id': '0000',
            'riddleparams': 0,
            'faults': 0,
            'animation': 0,
            'sentence': 0,
            'final_success': 0,
            'direction': 0,
            'riddle': 1,
            'animparams': 0,
            'checksum': 0
        })

    def test_legit_token(self):
        """Checks that an illegitimate token is not accepted"""

        a = Attempt(
            step=self.s1,
            challenge=self.s1.challenge,
            team=self.t1,
            submitter=self.t1u1,
            faults=0,
            points=0
        )
        # forge an attempt for the first step
        t_in = EncodedState({
            'id': '0000',
            'riddleparams': 0,
            'faults': 0,
            'animation': 0,
            'sentence': 0,
            'final_success': 0,
            'direction': 1,
            'riddle': 1,
            'animparams': 0,
            'checksum': 0
        })
        t_in['id'] = self.t1.laumio
        t_in['direction'] = 1
        t_in['final_succes'] = 1
        a.token_in = t_in

        t_out = EncodedState({
            'id': '0000',
            'riddleparams': 0,
            'faults': 0,
            'animation': 0,
            'sentence': 0,
            'final_success': 0,
            'direction': 1,
            'riddle': 1,
            'animparams': 0,
            'checksum': 0
        })
        t_out['id'] = self.t1.laumio
        t_out['riddle'] += 1
        t_out['direction'] = 0
        a.token_out = t_out
        a.save()

        # prepare mailiciously forged token
        ft = EncodedState({
            'id': '0000',
            'riddleparams': 0,
            'faults': 0,
            'animation': 0,
            'sentence': 0,
            'final_success': 0,
            'direction': 1,
            'riddle': 1,
            'animparams': 0,
            'checksum': 0
        })
        ft['id'] = self.t1.laumio
        ft['direction'] = 1
        ft['riddle'] += 2  # <= illegal modification of riddle ID
        response = self.client.get(reverse('propose_token', args=[self.t1u1.pseudo, str(ft)]))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'illegal token',
                'command': 'propose_token',
                'result': {
                    'modified_fields': ['riddle'],
                }
            }
        )

    def test_reject_wrong_team(self):
        """Token for team 1 submitted by a member of team B must be rejected"""
        t = self.basetoken
        t['id'] = self.t1.laumio
        t['direction'] = 1
        t['final_succes'] = 1
        response = self.client.get(reverse('propose_token', args=[self.t2u1.pseudo, str(t)]))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'submitter not part of team',
                'command': 'propose_token',
                'result': {
                    'submitter_team': self.t2.name,
                    'token_team': self.t1.name
                }
            }
        )

    def test_reject_wrong_direction(self):
        """Any token with the wrong direction bit must be rejected"""
        t = self.basetoken
        t['id'] = self.t1.laumio
        t['direction'] = 0
        response = self.client.get(reverse('propose_token', args=[self.t1u1.pseudo, str(t)]))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'wrong direction',
                'command': 'propose_token',
                'result': []
            }
        )

    def test_reject_wrong_checksum(self):
        """Any token with an incorrect checeksum must be rejected"""
        t = FakeEncState(self.basetoken.D)
        t['id'] = self.t1.laumio
        t['direction'] = 1
        response = self.client.get(reverse('propose_token', args=[self.t1u1.pseudo, str(t)]))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'incorrect checksum',
                'command': 'propose_token',
                'result': []
            }
        )

    def test_accept_first_token(self):
        """The first token must be valid and the team ID extracted"""

        self.maxDiff = None
        # create a new, bare team, with one member
        t = Team.objects.create(name="Corrino")
        m = Member.objects.create(pseudo="Idaho", team=t)

        t_in = copy.deepcopy(self.basetoken)
        t_in['direction'] = 1
        t_in['riddle'] = 0
        t_in['final_success'] =1
        t_in['id'] = 0x0042

        t_out = copy.deepcopy(self.basetoken)
        t_out['direction'] = 0
        t_out['riddle'] = 1
        t_out['final_success'] = 0
        t_out['id'] = 0x0042

        response = self.client.get(reverse('propose_token', args=[m.pseudo, str(t_in)]))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'valid token',
                'command': 'propose_token',
                'result': {
                    'next': {
                        'token': str(t_out),
                        'next': self.s1.challenge.name,
                        'type': 'riddle'
                    }
                }
            }
        )
        team = Team.objects.get(pk=t.id)
        self.assertEqual(team.laumio, '0042')

    def test_jailing(self):
        """Checks that server sends back a jail token if is_success=False"""

        # forge an attempt for the first step
        t_in = self.basetoken
        t_in['id'] = self.t1.laumio
        t_in['direction'] = 1
        t_in['final_succes'] = 1

        t_out = self.basetoken
        t_out['id'] = self.t1.laumio
        t_out['riddle'] += self.s1.challenge.index
        t_out['direction'] = 0

        previous_score = S.completed_riddle(self.s1.index)['score']
        Attempt.objects.create(
            step=self.s1,
            challenge=self.s1.challenge,
            team=self.t1,
            submitter=self.t1u1,
            token_in=str(t_in),
            token_out=str(t_out),
            faults=t_out['faults'],
            points=previous_score
        )

        self.t1.step = self.s1
        self.t1.jail = False
        self.t1.challenge = self.s2.challenge
        self.t1.score = previous_score
        self.t1.save()

        proposed_t = copy.deepcopy(t_out)
        proposed_t['direction'] = 1
        proposed_t['final_success'] = 0  # <= failed riddle
        proposed_t['faults'] = 5

        response = self.client.get(reverse('propose_token', args=[self.t1u1.pseudo, str(proposed_t)]))

        team = Team.objects.get(laumio=self.t1.laumio)
        response_dict = json.loads(response.content.decode('utf8'))
        response_token = EncodedState().from_string(response_dict['result']['next']['token'])

        self.assertIn(
            response_token['riddle'],
            [_.index for _ in self.s1.jails.all()]
        )
        self.assertEqual(team.score, previous_score-team.step.index**2)

    def test_increment_riddle(self):
        """Checks that the server correctly follows the riddle serie"""
        # forge an attempt for the first step
        t_in = copy.deepcopy(self.basetoken)
        t_in['id'] = self.t1.laumio
        t_in['direction'] = 1
        t_in['final_succes'] = 1

        t_out = copy.deepcopy(self.basetoken)
        t_out['id'] = self.t1.laumio
        t_out['riddle'] += self.s0.challenge.index
        t_out['direction'] = 0

        previous_score = S.completed_riddle(self.s0.index)['score']
        Attempt.objects.create(
            step=self.s0,
            challenge=self.s0.challenge,
            team=self.t1,
            submitter=self.t1u1,
            token_in=str(t_in),
            token_out=str(t_out),
            faults=t_out['faults'],
            points=previous_score
        )

        self.t1.step = self.s1
        self.t1.jail = False
        self.t1.challenge = self.s1.challenge
        self.t1.save()

        proposed_t = copy.deepcopy(t_out)
        proposed_t['direction'] = 1
        proposed_t['final_success'] = 1  # <= ok riddle
        proposed_t['faults'] = 0

        response_t = copy.deepcopy(self.basetoken)
        response_t['id'] = self.t1.laumio
        response_t['riddle'] = self.s2.challenge.index
        response_t['direction'] = 0

        response = self.client.get(reverse('propose_token', args=[self.t1u1.pseudo, str(proposed_t)]))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'status': 'valid token',
                'command': 'propose_token',
                'result': {
                    'next': {
                        'token': str(response_t),
                        'next': self.s2.challenge.name,
                        'type': 'riddle'
                    }
                }
            }
        )
        team = Team.objects.get(laumio=self.t1.laumio)
        self.assertEqual(team.score, previous_score+2**self.s1.index)


class FakeEncState(EncodedState):

    def compute_checksum(self):
        return 1
