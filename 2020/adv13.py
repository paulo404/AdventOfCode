#!/usr/bin/env python3
import sys
import math
import functools as ft
import operator

def lcm(a, b):
    return abs(a*b) // math.gcd(a,b)

def part1( st, ids ):
    rl = [ ( math.ceil(st/p) * p ) - st for p in ids ]
    ind = rl.index(min( rl ))
    return ids[ind] * rl[ind]

def part2( ids, start ):
    t = start
    step = 1
    matches = 0

    while True:
        departed_in_seq = [ (t+i) % ids[i] == 0 for i in range(len(ids)) ]
        found = ft.reduce( operator.and_, departed_in_seq )
        if found: break

        #update step if was able to match a new number
        match_ind = [ i for i,x in enumerate(departed_in_seq) if x ]
        new_matches = [ ids[i] for i in match_ind ]
        if len(new_matches) > matches:
            step = ft.reduce( lcm, new_matches )
        t += step
    return t

if __name__ == '__main__':
    inp = [ s for s in [ x.strip() for x in sys.stdin.readlines() ] ]

    st, pl = int(inp[0]), [ int(p) for p in inp[1].split(",") if p != "x" ]
    print( "Part 1: %d" % ( part1( st,pl ) ) )

    pl = [ 1 if p == "x" else int(p) for p in inp[1].split(",") ]
    print( "Part 2: %d" % ( part2(pl, 0 ) ) )
