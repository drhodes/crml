#! /usr/bin/env python
import sys


# this is so easy I feel bad.
for line in sys.stdin:
    for char in line:
        val = hex(ord(char))[2:]
        if len(val) < 2:
            sys.stdout.write("0" + val)
        else:
            sys.stdout.write(val)
        
