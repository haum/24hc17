from django.db import models as M
from .encodedstate import EncodedState

class Animation(M.Model):
    """ Animation in the Laumio
    name -- animation name
    index -- index in the Laumio's table
    """

    name = M.TextField(max_length=100)
    index = M.IntegerField(default=0)
    params = M.IntegerField(default=0)

    def __str__(self):
        return self.name


class Challenge(M.Model):
    """ Challenge

    name -- challenge's name
    description -- description of the challenge
    index -- index of the challenge on the laumio
    """

    name = M.TextField(max_length=200)
    description = M.TextField(max_length=1000, blank=True, null=True)
    index = M.IntegerField(default=0)
    params = M.IntegerField(default=0)
    is_jail = M.BooleanField(default=False)

    def __str__(self):
        return self.name

    def asdict(self):
        return {
            'name': self.name,
            'description': self.description,
            'index': self.index
        }


class Step(M.Model):
    """
    A step in the line of riddles
    """
    index = M.IntegerField(null=True, blank=True)
    challenge = M.ForeignKey(Challenge)
    animation = M.ForeignKey(Animation)
    jails = M.ManyToManyField(Challenge, blank=True, related_name='jails')
    is_jail = M.BooleanField(default=False)

    def __str__(self):
        jailcount = self.jails.count()
        return "Step %d using challenge %s (%d jails)"%(self.index, str(self.challenge), jailcount)

    def asdict(self, challenges=True):
        dictrepr = {
            'index': self.index,
        }
        if challenges:
            dictrepr['challenge'] = self.challenge.asdict()
            dictrepr['jails'] = [_.asdict() for _ in self.jails.all()]
        return dictrepr


class Team(M.Model):
    """ Team

    name -- Team's name
    location -- physical location
    score -- score
    """

    name = M.TextField(max_length=200, unique=True)
    location = M.TextField(max_length=200, default='')
    laumio = M.TextField(max_length=4, default='')
    score = M.IntegerField(default=0)
    jail = M.BooleanField(default=False)
    step = M.ForeignKey(Step, null=True)
    challenge = M.ForeignKey(Challenge, null=True)

    def __str__(self):
        return self.name

    def asdict(self, members=False):
        dictrepr = {
            'name': self.name,
            'location': self.location,
            'score': self.score,
            'laumio': self.laumio
        }
        if members:
            dictrepr['members'] = [_.asdict(team=False) for _ in self.member_set.filter(primary=True)]
        return dictrepr


class Member(M.Model):
    """ Team Member

    pseudo -- IRC Pseudo
    primary -- is this the main pseudo of the user or just a variant
    mainentry -- "main pseudo" to which this variant is like
    team -- User's team
    """

    pseudo = M.TextField(max_length=200, unique=True)
    primary = M.BooleanField(default=True)
    mainentry = M.ForeignKey('Member', blank=True, null=True)
    team = M.ForeignKey('Team')

    def __str__(self):
        if self.primary:
            return "%s (%s)"%(self.pseudo, self.team)
        else:
            return "%s aka. %s (%s)"%(self.pseudo, self.mainentry, self.team)

    def asdict(self, team=True):
        """Return a dict representation of the object"""

        dictrepr = {
            'pseudo': self.pseudo,
            'primary': self.primary,
        }
        if team:
            dictrepr['team'] = self.team.asdict()
        if not self.primary:
            dictrepr['mainentry'] = self.mainentry.asdict()
        return dictrepr


class Attempt(M.Model):
    """ Attempt to a Challenge

    team -- responsible team
    token_in -- token sent to unlock (from team)
    token_out -- token sent back to the team
    faults -- number of faults
    points -- number of points earnt from this attempt
    timestamp --
    """

    timestamp = M.DateTimeField(auto_now_add=True)
    step = M.ForeignKey(Step)
    challenge = M.ForeignKey(Challenge)
    jail = M.BooleanField(default=False)
    success = M.BooleanField(default=False)
    team = M.ForeignKey(Team)
    submitter = M.ForeignKey(Member)
    token_in = M.TextField(max_length=22)
    token_out = M.TextField(max_length=22)
    faults = M.IntegerField(default=0)
    points = M.IntegerField(default=0)

    def __str__(self):
        return "Attempt from %s at %s on %s"%(self.team, self.timestamp, self.step)

    def decode_token_to_dict(self, token_str):
        return EncodedState().from_string(token_str).D

    def asdict(self, team=True):
        return {
            'date': self.timestamp.timestamp(),
            'points': self.points,
            'step': self.step.asdict(),
            'faults': self.faults,
            'submitter': self.submitter.asdict(team=team),
            'tokens': {
                'in': {
                    'as_str': self.token_in,
                    'decoded': self.decode_token_to_dict(self.token_in)
                },
                'out': {
                    'as_str': self.token_out,
                    'decoded': self.decode_token_to_dict(self.token_out)
                }
            },
        }


class MessageType(M.Model):
    """ Message Type
    name --
    """

    name = M.TextField(max_length=100)

    def __str__(self):
        return self.name


class Message(M.Model):
    """ Message in the Laumio
    message -- message's text
    index -- index in the Laumio's table
    type -- type of message
    """

    message = M.TextField(max_length=200)
    index = M.IntegerField(default=0)
    type = M.ForeignKey('MessageType')

    def __str__(self):
        return "(%s) %s"%(self.type, self.message)


