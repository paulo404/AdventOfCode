#!/usr/bin/env python3
import sys
import numpy as np
from parse import parse
import code
from collections import defaultdict,Counter
from functools import reduce
from operator import iconcat

TILESIZE = 10

def getsides( tile ) :
    sides = tile[0], tile[0:TILESIZE,TILESIZE-1], tile[TILESIZE-1], tile[0:TILESIZE,0]
    return [tuple(s) for s in sides]

def fliph( tile ) : return np.flip(tile,1)

def flipv( tile ) : return np.flip(tile,0)

#NOTE idea: checkboard of tiles for failling faster
def part1():
    #if odd has to be an edge
    dicts = tws_d, tws_v, tws_h
    possible_sides = set(list(tws_d.keys()) + list(tws_v.keys()) + list(tws_h.keys()))
    border_side  = {}
    for side in possible_sides :
        #queries = [ d.get(side,0) for d in dicts ]
        queries = tws_d.get(side,[]) #NOTE only looking at the default orientation for now
        if len(queries) % 2 == 1 :
            border_side[side] = queries

    btiles = reduce( iconcat, border_side.values() )
    possible_corners = [item for item, count in Counter(btiles).items() if count > 1] #NOTE doomed idea?
    print(possible_corners)
    print(len(possible_corners))
    print(len(tiles))
    pass

if __name__ == '__main__' :
    #parse
    tiles = {}
    while True :
        if (line := sys.stdin.readline().strip()) == '' : break
        tid, *_ = parse("Tile {:d}:", line)
        tile = np.empty((TILESIZE,TILESIZE),str)
        for l in range(TILESIZE) :
            tile[l] = list(sys.stdin.readline().strip())
        tiles[tid] = tile
        sys.stdin.readline()

    #sides{tid} = [N,E,S,W]
    sides = {}
    #tiles with side[side] = [tid,...]
    tws_d, tws_v, tws_h = defaultdict(list),defaultdict(list),defaultdict(list)
    for tid,tile in tiles.items() :
        tsides = getsides(tile)
        sides[tid] = tsides

        #can be flipped hor or ver
        for d in tsides                : tws_d[d].append(tid)
        for d in getsides(flipv(tile)) : tws_v[d].append(tid)
        for d in getsides(fliph(tile)) : tws_h[d].append(tid)
    print( f"Part 1: {part1()}")
