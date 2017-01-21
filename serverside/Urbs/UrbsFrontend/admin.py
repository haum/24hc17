from django.contrib import admin

from .models import Animation, Challenge, Step, Team, Member, Attempt, MessageType, Message

# # class TeamAdmin(admin.ModelAdmin):

class StepAdmin(admin.ModelAdmin):

    model = Step
    list_display = ['index', '__str__']

class AttemptAdmin(admin.ModelAdmin):

    model = Attempt
    list_filter = ['team__name', 'submitter__pseudo']

class MemberAdmin(admin.ModelAdmin):

    model = Member
    list_display = ['pseudo', 'team', 'related_teamlaumio']
    list_filter = ['team']

    def related_teamlaumio(self, obj):
        return obj.team.laumio
    related_teamlaumio.short_description = "Laumio's ID"

class TeamAdmin(admin.ModelAdmin):

    model = Team
    list_display = ['name', 'score', 'laumio', 'step', 'related_stepindex']

    def related_stepindex(self, obj):
        return obj.step.index
    related_stepindex.short_description = "Position in tree"




# admin.site.register(Team, TeamAdmin)
admin.site.register(Animation)
admin.site.register(Challenge)
admin.site.register(Team, TeamAdmin)
admin.site.register(Step, StepAdmin)
admin.site.register(Member, MemberAdmin)
admin.site.register(Attempt, AttemptAdmin)
admin.site.register(MessageType)
admin.site.register(Message)
