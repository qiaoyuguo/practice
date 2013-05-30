#!/usr/bin/env python
# -*- coding: utf-8 -*-

# get id of the last inserted row by using lastrowid attribute of the
# cursor object

import sqlite3 as lite
import sys

# create table in memory
con = lite.connect(':memory:')

with con:
    cur = con.cursor()
    cur.execute("CREATE TABLE Friends(Id INTEGER PRIMARY KEY, Name TEXT)")
    cur.execute("INSERT INTO Friends(Name) VALUES ('Tom');")
    cur.execute("INSERT INTO Friends(Name) VALUES ('Rebecca');")
    cur.execute("INSERT INTO Friends(Name) VALUES ('Jim');")
    cur.execute("INSERT INTO Friends(Name) VALUES ('Robert')")

    lid = cur.lastrowid
    print "The last id of the inserted row is %d" % lid
