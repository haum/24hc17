from django.db import models as M

class Team(M.Model):
    """ Team

    name -- Team's name
    location -- physical location
    score -- score
    """

    name = M.TextField(max_length=200)
    location = M.TextField(max_length=200, default='')
    score = M.IntegerField(default=0)

    def __str__(self):
        return self.name


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
            return "%s (%s)"%(self.pseudo,self.team)
        else:
            return "%s aka. %s (%s)"%(self.pseudo,self.mainentry, self.team)


class Challenge(M.Model):
    """ Challenge

    name -- challenge's name
    description -- description of the challenge
    index -- index of the challenge on the laumio
    """

    name = M.TextField(max_length=200)
    description = M.TextField(max_length=1000, blank=True, null=True)
    index = M.IntegerField(default=0)

    def __str__(self):
        return self.name


class Step(M.Model):
    """
    A step in the line of riddles
    """
    index = M.IntegerField(null=True, blank=True)
    challenge = M.ForeignKey(Challenge)
    next_challenge = M.ForeignKey('self', blank=True, null=True)
    jails = M.ManyToManyField(Challenge, blank=True, related_name='jails')

    def __str__(self):
        jailcount = self.jails.count()
        return "Step %d using challenge %s (%d jails)"%(self.index, str(self.challenge), jailcount)


class Attempt(M.Model):
    """ Attempt to a Challenge

    team -- responsible team
    leaf -- answered challenge (RTLeaf)
    token_in -- token sent to unlock (from team)
    token_out -- token sent back to the team
    faults -- number of faults
    points -- number of points earnt from this attempt
    timestamp --
    """

    timestamp = M.DateTimeField(auto_now_add=True)
    step = M.ForeignKey(Step)
    jail = M.BooleanField(default=False)
    token_in = M.TextField(max_length=100)
    token_out = M.TextField(max_length=100)
    faults = M.IntegerField(default=0)
    points = M.IntegerField(default=0)

    def __str__(self):
        "Attempt from %s at %s on %s"%(self.team, self.timestamp, self.leaf)


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


class Animation(M.Model):
    """ Animation in the Laumio
    name -- animation name
    index -- index in the Laumio's table
    """

    name = M.TextField(max_length=100)
    index = M.IntegerField(default=0)

    def __str__(self):
        return self.name
