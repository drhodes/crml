#! /usr/bin/env python
import sys

hexes = dict(zip("0123456789abcdef", range(16)))

def hexof(a, b):
    '''
    take a, b | a and b are strings [1..9] + [a..f]
    a == 2^16, b == 1^16
    '''
    vala = 16 * hexes[a] 
    valb = hexes[b]
    return vala+valb

def quit():
    sys.stderr.write("Bad Data\n")
    sys.exit()


for line in sys.stdin:    
    if len(line) % 2 != 0:
        quit()
    for i in xrange(len(line)/2):
        a, b = line[i*2], line[i*2+1]        
        if a not in "01234567890abcdef":
            quit()
        if b not in "01234567890abcdef":
            quit()
        sys.stdout.write(chr(hexof(a,b)))
        
