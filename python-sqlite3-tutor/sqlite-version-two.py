#!/usr/bin/env python
# -*- coding: utf-8 -*-

# get version of sqlite database using "with" keyword

import sqlite3 as lite
import sys

con = lite.connect('test.db')

with con:
    cur = con.cursor()
    cur.execute('SELECT SQLITE_VERSION()')
    data = cur.fetchone()
    print "SQLite version: %s" % data

