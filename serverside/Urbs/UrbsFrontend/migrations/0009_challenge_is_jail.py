# -*- coding: utf-8 -*-
# Generated by Django 1.10.5 on 2017-01-14 22:21
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('UrbsFrontend', '0008_auto_20170114_1557'),
    ]

    operations = [
        migrations.AddField(
            model_name='challenge',
            name='is_jail',
            field=models.BooleanField(default=False),
        ),
    ]
