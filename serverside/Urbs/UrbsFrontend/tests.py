from django.test import TestCase
from django.urls import reverse

import json

from .models import Team, Member


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
                        'score': 0
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
            score=3
        )

        cls.t2 = Team.objects.create(
            name='Atreides',
            location='Arakis',
            score=42
        )
        cls.u1 = Member.objects.create(pseudo='Leto', team=cls.t2)
        cls.u2 = Member.objects.create(pseudo='Paul', team=cls.t2)

    def test_without_users(self):
        """Test the output of the view if the team has no user"""
        response = self.client.get(reverse('team#get_team', args=[self.t1.name]))
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
        response = self.client.get(reverse('team#get_team', args=[self.t2.name]))
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
        response = self.client.get(reverse('team#get_team', args=['corrino']))
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
            score=3
        )

        cls.t2 = Team.objects.create(
            name='Atreides',
            location='Arakis',
            score=42
        )
        cls.u1 = Member.objects.create(pseudo='Leto', team=cls.t2)
        cls.u2 = Member.objects.create(pseudo='Paul', team=cls.t2)

    def test_without_users(self):
        """Test the output of the view if the team has no user"""
        response = self.client.get(reverse('team#members', args=[self.t1.name]))
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
        response = self.client.get(reverse('team#members', args=[self.t2.name]))
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
        response = self.client.get(reverse('team#members', args=['corrino']))
        self.assertEqual(
            json.loads(response.content.decode('utf8')),
            {
                'command': 'get_team_members',
                'status': 'unknown team',
                'result': []
            }
        )
