#!/usr/bin/env pyton
# -*- coding: utf-8 -*-

import sqlite3 as lite
import sys

uId = 1
uPrice = 62300

con = lite.connect('test.db')

with con:
    cur = con.cursor()
    cur.execute("UPDATE Cars SET Price=? where Id=?", (uPrice, uId))
    con.commit()
    print "Number of rows updatd: %d" % cur.rowcount
