from django.db import models as M

class Team(M.Model):
    """ Team

    name -- Team's name
    location -- physical location
    score -- score
    """

    name = M.TextField(max_length=200)
    location = M.TextField(max_length=200)
    score = M.IntegerField(default=0)

    def __unicode__(self):
        return self.name


class Member(M.Model):
    """ Team Member

    pseudo -- IRC Pseudo
    token --  used to detect pseudo variants
    primary -- is this the main pseudo of the user or just a variant
    mainentry -- "main pseudo" to which this variant is like
    team -- User's team
    """

    pseudo = M.TextField(max_length=200)
    token = M.TextField(max_length=100, unique=True)
    primary = M.BooleanField(default=True)
    mainentry = M.ForeignKey('Member', blank=True, null=True)
    team = M.ForeignKey('Team')

    def __unicode__(self):
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

    def __unicode__(self):
        return self.name


class RiddleTree(M.Model):
    """ Riddle Tree
    name --
    """

    name = M.TextField(max_length=100)

    def __unicode__(self):
        return self.name


class RTLeaf(M.Model):
    """ Riddle Tree Leaf
    challenge --
    level -- level in the tree
    tree -- tree to which the leaf is linked
    """

    challenge = M.ForeignKey('Challenge')
    level = M.IntegerField(default=0)
    tree = M.ForeignKey('RiddleTree')

    def __unicode__(self):
        return "%s (at level %d of %s)"%(self.challenge, self.level, self.tree)


class RTBranch(M.Model):
    """ Riddle Tree branch

    from_leaf -- RTLeaf at the beginning
    to_leaf -- RTLeaf at the end
    tree -- tree to which the leaf is linked
    """

    from_leaf = M.ForeignKey('RTLeaf', related_name='branchstarting')
    to_leaf = M.ForeignKey('RTLeaf', related_name='branchending')
    tree = M.ForeignKey('RiddleTree')

    def __unicode__(self):
        return "%s ==> %s"%(self.from_leaf, self.to_leaf)



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
    leaf = M.ForeignKey('Team')
    leaf = M.ForeignKey('RTLeaf')
    token_in = M.TextField(max_length=100)
    token_out = M.TextField(max_length=100)
    faults = M.IntegerField(default=0)
    points = M.IntegerField(default=0)

    def __unicode__(self):
        "Attempt from %s at %s on %s"%(self.team, self.timestamp, self.leaf)


class MessageType(M.Model):
    """ Message Type
    name --
    """

    name = M.TextField(max_length=100)

    def __unicode__(self):
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

    def __unicode__(self):
        return "(%s) %s"%(self.type, self.message)


class Animation(M.Model):
    """ Animation in the Laumio
    name -- animation name
    index -- index in the Laumio's table
    """

    name = M.TextField(max_length=100)
    index = M.IntegerField(default=0)

    def __unicode__(self):
        return self.name
