from django.contrib import admin

from .models import Animation, Challenge, Step, Team, Member, Attempt, MessageType, Message

# # class TeamAdmin(admin.ModelAdmin):

class StepAdmin(admin.ModelAdmin):

    model = Step
    list_display = ['index', '__str__']


# admin.site.register(Team, TeamAdmin)
admin.site.register(Animation)
admin.site.register(Challenge)
admin.site.register(Team)
admin.site.register(Step, StepAdmin)
admin.site.register(Member)
admin.site.register(Attempt)
admin.site.register(MessageType)
admin.site.register(Message)
