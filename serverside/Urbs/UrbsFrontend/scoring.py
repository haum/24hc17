#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# scoring.py
#
# Copyright © 2017 Mathieu Gaborit (matael) <mathieu@matael.org>
#
# Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
# Mathieu (matael) Gaborit wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and you
# think this stuff is worth it, you can buy me a beer or coffee in return
#


class Scorer:
    """ All functions return a tuple (number of points, next step, jail)"""

    @classmethod
    def completed_riddle(cls, step):
        return {
            'score': step**2,
            'next_id': step+1,
            'jail': False
        }

    @classmethod
    def failed_riddle(cls, step):
        return {
            'score': -3*step,
            'next_id': step,
            'jail': True
        }

    @classmethod
    def completed_jail(cls, step):
        return {
            'score': 0,
            'next_id': step,
            'jail': False
        }

    @classmethod
    def failed_jail(cls, step):
        return {
            'score': -step**2,
            'next_id': step,
            'jail': True
        }
