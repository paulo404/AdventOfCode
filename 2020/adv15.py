#!/usr/bin/env python3
import sys
import re

def part1( inp, till ):
    said, last, curr = [None]*till, 0, 0
    for i in range( 1, till +1 ):
        last = curr
        if i-1 < len(inp):
            curr = inp[i-1]
        else:
            if said[last] == None: curr = 0
            else: curr = i-1 - said[last]

        said[last] = i-1

    return curr

if __name__ == '__main__':
    inp = [ int(x) for x in sys.stdin.readline().split(',') ]

    print( "Part 1: %d" % ( part1( inp, 2020 ) ) )
    print( "Part 2: %d" % ( part1( inp, 30000000 ) ) )
