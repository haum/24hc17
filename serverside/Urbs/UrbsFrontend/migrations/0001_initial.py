# -*- coding: utf-8 -*-
# Generated by Django 1.10.3 on 2016-11-21 22:49
from __future__ import unicode_literals

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Animation',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.TextField(max_length=100)),
                ('index', models.IntegerField(default=0)),
            ],
        ),
        migrations.CreateModel(
            name='Attempt',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('timestamp', models.DateTimeField(auto_now_add=True)),
                ('token_in', models.TextField(max_length=100)),
                ('token_out', models.TextField(max_length=100)),
                ('faults', models.IntegerField(default=0)),
                ('points', models.IntegerField(default=0)),
            ],
        ),
        migrations.CreateModel(
            name='Challenge',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.TextField(max_length=200)),
                ('description', models.TextField(blank=True, max_length=1000, null=True)),
                ('index', models.IntegerField(default=0)),
            ],
        ),
        migrations.CreateModel(
            name='Member',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('pseudo', models.TextField(max_length=200)),
                ('token', models.TextField(max_length=100, unique=True)),
                ('primary', models.BooleanField(default=True)),
                ('mainentry', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='UrbsFrontend.Member')),
            ],
        ),
        migrations.CreateModel(
            name='Message',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('message', models.TextField(max_length=200)),
                ('index', models.IntegerField(default=0)),
            ],
        ),
        migrations.CreateModel(
            name='MessageType',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.TextField(max_length=100)),
            ],
        ),
        migrations.CreateModel(
            name='RiddleTree',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.TextField(max_length=100)),
            ],
        ),
        migrations.CreateModel(
            name='RTBranch',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
            ],
        ),
        migrations.CreateModel(
            name='RTLeaf',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('level', models.IntegerField(default=0)),
                ('challenge', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='UrbsFrontend.Challenge')),
                ('tree', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='UrbsFrontend.RiddleTree')),
            ],
        ),
        migrations.CreateModel(
            name='Team',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.TextField(max_length=200)),
                ('location', models.TextField(max_length=200)),
                ('score', models.IntegerField(default=0)),
            ],
        ),
        migrations.AddField(
            model_name='rtbranch',
            name='from_leaf',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='branchstarting', to='UrbsFrontend.RTLeaf'),
        ),
        migrations.AddField(
            model_name='rtbranch',
            name='to_leaf',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='branchending', to='UrbsFrontend.RTLeaf'),
        ),
        migrations.AddField(
            model_name='rtbranch',
            name='tree',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='UrbsFrontend.RiddleTree'),
        ),
        migrations.AddField(
            model_name='message',
            name='type',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='UrbsFrontend.MessageType'),
        ),
        migrations.AddField(
            model_name='member',
            name='team',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='UrbsFrontend.Team'),
        ),
        migrations.AddField(
            model_name='attempt',
            name='leaf',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='UrbsFrontend.RTLeaf'),
        ),
    ]