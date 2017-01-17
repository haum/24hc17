#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# urls.py
#
# Copyright © 2016 Mathieu Gaborit (matael) <mathieu@matael.org>
#
# Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
# Mathieu (matael) Gaborit wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and you
# think this stuff is worth it, you can buy me a beer or coffee in return
#

from django.conf.urls import url, include

from .views import\
    get_user,\
    get_all_users,\
    register_user,\
    get_team,\
    get_team_members,\
    get_team_record,\
    get_all_teams,\
    propose_token

urlpatterns = [
    url(r'^user/', include([
        url(r'all/?', get_all_users, name='user#all'),
        url(r'(?P<username>[A-Za-z0-9\-_]+)/?', get_user, name='user#get_user'),
    ])),
    url(r'^team/', include([
        url(r'all/?', get_all_teams, name='team#all'),
        url(r'(?P<teamname>[A-Za-z0-9\-_]+)/adduser/(?P<username>[A-Za-z0-9\-_]+)?', register_user, name='team#register_user'),
        url(r'(?P<teamid>[A-Za-z0-9\-_]+)/members/?', get_team_members, name='team#members'),
        url(r'(?P<teamid>[A-Za-z0-9\-_]+)/record/?', get_team_record, name='team#record'),
        url(r'(?P<teamid>[A-Za-z0-9\-_]+)/?', get_team, name='team#get_team'),
    ])),
    url(r'^token/(?P<username>[A-Za-z0-9\-_]+)/(?P<token>[\w\d+*]{22})/?', propose_token, name='propose_token')
]
