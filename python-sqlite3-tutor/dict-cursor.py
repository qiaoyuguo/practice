#!/usr/bin/env python
# -*- coding: utf-8 -*-

# use dictionary cursor

import sqlite3 as lite

con = lite.connect('test.db')

with con:
    con.row_factory = lite.Row

    cur = con.cursor()
    cur.execute("SELECT * FROM Cars")

    rows = cur.fetchall()

    for row in rows:
        print "%s %s %s" % (row["Id"], row["Name"], row["Price"])
