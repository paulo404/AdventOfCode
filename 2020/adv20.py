#!/usr/bin/env python3
import sys
import numpy as np
from parse import parse
import code
from collections import defaultdict,Counter
from functools import reduce
from operator import iconcat

TILESIZE = 10
BIGSIDE = 12

def connectingSide( grid_entry, side ) :
    #print(' cs' + str(grid_entry) + side)
    tile,up_ind,flipmode = grid_entry
    side_ind = ['north','east','south','west'].index(side)
    return ct[tile][flipmode][(up_ind+side_ind) % 4]

def getmatches( side ) :
    matches = []
    for flip,d in enumerate([tws_d, tws_v, tws_h]) :
        if side in d :
            for tid,index in d[side] :
                matches.append( (tid,index,flip) )
    return matches

def getsides( tile ) :
    sides = tile[0], tile[0:TILESIZE,TILESIZE-1], tile[TILESIZE-1], tile[0:TILESIZE,0]
    return [tuple(s) for s in sides]

def fliph( tile ) : return np.flip(tile,1)

def flipv( tile ) : return np.flip(tile,0)

def dfs(grid,i,j,used) :
    print(i,j)
    if i == BIGSIDE : return True #end

    #checks
    matches_s, matches_e = [], []
    if looking_right := i > 0 :
        cs = connectingSide( grid[i-1,j], 'south' )
        #returns same tuple as compact_tile (tid,rot,flip)
        matches_s = getmatches( cs )
    if looking_left := j > 0 :
        cs = connectingSide( grid[i,j-1], 'east' )
        matches_e = getmatches( cs ) #TODO do i want the intersection of these 2?
    matches = (set(matches_s) & set(matches_e)) if looking_left and looking_right else matches_s + matches_e

    for match in matches :
        tid = match[0]
        if tid in used : continue
        grid[i,j] = match
        if res := dfs( grid, i+((j+1)//BIGSIDE), (j+1)%BIGSIDE, used+[tid] ) == True : return res

    return False

def part1():
    #try all passible initial tiles
    grid = np.empty( (BIGSIDE,BIGSIDE), tuple)
    for tid,v in ct.items() :
        for flip, sides in enumerate(v) :
            for rot in range(4) :
                grid[0,0] = (tid,rot,flip)
                if res := dfs( grid, 0, 1, [tid]) == True : return res
    return False

#NOTE idea: checkboard of tiles for failling faster
#def part1():
#    #if odd has to be an edge
#    dicts = tws_d, tws_v, tws_h
#    possible_sides = set(list(tws_d.keys()) + list(tws_v.keys()) + list(tws_h.keys()))
#    border_side  = {}
#    for side in possible_sides :
#        #queries = [ d.get(side,0) for d in dicts ]
#        queries = tws_d.get(side,[]) #NOTE only looking at the default orientation for now
#        if len(queries) % 2 == 1 :
#            border_side[side] = queries
#
#    btiles = reduce( iconcat, border_side.values() )
#    possible_corners = [item for item, count in Counter(btiles).items() if count > 1] #NOTE doomed idea?
#    print(possible_corners)
#    print(len(possible_corners))
#    print(len(tiles))

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
    sides, ct = {}, {}
    #tiles with side[side] = [tid,...]
    tws_d, tws_v, tws_h = defaultdict(list),defaultdict(list),defaultdict(list)
    for tid,tile in tiles.items() :
        tile_sides = getsides(tile)
        tile_sides_v = getsides(flipv(tile))
        tile_sides_h = getsides(fliph(tile))

        sides[tid] = tile_sides

        #can be flipped hor or ver
        for i,d in enumerate(tile_sides)   : tws_d[d].append( (tid,i) )
        for i,d in enumerate(tile_sides_v) : tws_v[d].append( (tid,i) )
        for i,d in enumerate(tile_sides_h) : tws_h[d].append( (tid,i) )

        # [ entry(noflip),entry(flipv),entry(fliph) ] entry =[]
        # it stands for compact tile (only sides information) (yes this name blows and sucks, so i guess it evens out)
        ct[tid] = [tile_sides, tile_sides_v, tile_sides_h]

    print( f"Part 1: {part1()}")
