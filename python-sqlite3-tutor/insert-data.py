#!/usr/bin/env python
# -*- coding:utf-8 -*-

# create a Cars table and insert several rows to it.

import sqlite3 as lite
import sys

con = lite.connect('test.db')

with con:
    cur = con.cursor()
    cur.execute("CREATE TABLE Cars(Id INT, Name TEXT, Price INT)")
    cur.execute("INSERT INTO Cars VALUES(1, 'Audi', 52642)")
    cur.execute("INSERT INTO Cars VALUES(2, 'Mercedes', 57123)")
    cur.execute("INSERT INTO Cars VALUES(3, 'Skoda', 9000)")
    cur.execute("INSERT INTO Cars VALUES(4, 'Volvo', 29000)")
    cur.execute("INSERT INTO Cars VALUES(5, 'Bentley',350000)")
    cur.execute("INSERT INTO Cars VALUES(6, 'Citroen', 21000)")
    cur.execute("INSERT INTO Cars VALUES(7, 'Hummer', 41400)")
    cur.execute("INSERT INTO Cars VALUES(8, 'Volksagen', 21600)")
