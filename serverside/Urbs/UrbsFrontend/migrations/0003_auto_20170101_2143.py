# -*- coding: utf-8 -*-
# Generated by Django 1.10.4 on 2017-01-01 21:43
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('UrbsFrontend', '0002_auto_20170101_2033'),
    ]

    operations = [
        migrations.AlterField(
            model_name='team',
            name='location',
            field=models.TextField(blank=True, max_length=200, null=True),
        ),
    ]
