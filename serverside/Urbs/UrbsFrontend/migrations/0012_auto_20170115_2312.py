# -*- coding: utf-8 -*-
# Generated by Django 1.10.5 on 2017-01-15 23:12
from __future__ import unicode_literals

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('UrbsFrontend', '0011_auto_20170115_2244'),
    ]

    operations = [
        migrations.AddField(
            model_name='team',
            name='challenge',
            field=models.ForeignKey(default=1, on_delete=django.db.models.deletion.CASCADE, to='UrbsFrontend.Challenge'),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='team',
            name='jail',
            field=models.BooleanField(default=False),
        ),
        migrations.AddField(
            model_name='team',
            name='step',
            field=models.ForeignKey(default=0, on_delete=django.db.models.deletion.CASCADE, to='UrbsFrontend.Step'),
            preserve_default=False,
        ),
    ]
