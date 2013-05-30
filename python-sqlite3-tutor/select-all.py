#!/usr/bin/env python
# -*- coding: utf-8 -*-

# get data in Cars Table using select 

import sqlite3 as lite
import sys
con = lite.connect('test.db')

with con:
    cur = con.cursor()
    cur.execute("SELECT * FROM  Cars")
    
    rows = cur.fetchall()
    
    for row in rows:
        print row


