#! /usr/bin/env python

import sys

infilename = sys.argv[1]
if not infilename.endswith(".hex"):
    print "File type error:"
    print "This program can only process .hex files"
    sys.exit()


outfilename = infilename.replace(".hex", ".hex.js")

def write_header(outfile, array_name):
    outfile.write("%s = [" % array_name)

def write_tail(outfile):
    outfile.write("];\n")

def write_some(outfile, bytes, block):
    print "writing block", block
    outfile.write('"')
    outfile.write(bytes)
    outfile.write('",\n')


def main():
    infile = open(infilename)
    outfile = open(outfilename, 'w')
    outfile.close()
    outfile = open(outfilename, 'a')

    print infilename
    print outfilename

    array_name = "_"+infilename.replace('.', '_')
    
    write_header(outfile, array_name)

    block = 0
    blocksize = 8192*4
    while infile:        
        bs = infile.read(blocksize);
        if bs == "": break
        write_some(outfile, bs, block)
        block += 1
    write_tail(outfile)
    outfile.close()



main()


