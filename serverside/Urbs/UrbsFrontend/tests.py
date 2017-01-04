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
