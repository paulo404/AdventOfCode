import sys
import numpy as np

def rotateOrientation( orient, ang ):
    # E, S, W, N aka clockwise
    direc = [ (1,0), (0,-1), (-1,0), (0,1) ]
    d_index = int(ang/90)
    return direc[ (direc.index(orient)+d_index) % len(direc) ]

def rotatePosition( pos, ang ):
    turns = int(ang/90)
    for i in range(abs(turns)):
        if turns > 0:
            pos = [+pos[1], -pos[0]]
        else:
            pos = [-pos[1], +pos[0]]
    return pos

def part1( inp ):
    orig, orient = [0,0], (1,0)
    pos = orig

    for c,v in inp:
        if   c == "F": pos = [ sum(x) for x in zip(pos, [ y*v for y in orient]) ]
        elif c == "N": pos[1] += v
        elif c == "S": pos[1] -= v
        elif c == "E": pos[0] += v
        elif c == "W": pos[0] -= v
        elif c == "R": orient = rotateOrientation(orient, +v)
        elif c == "L": orient = rotateOrientation(orient, -v)
        else:
            print("ratiei: " + c)
            exit()

    return abs(pos[0]) + abs(pos[1])

def part2( inp ):
    pos_way, orient_way = [10,1], (1,0)
    pos = orig = [0,0]

    for c,v in inp:
        if   c == "F": pos = [ sum(x) for x in zip( pos, [y*v for y in pos_way] ) ]
        elif c == "N": pos_way[1] += v
        elif c == "S": pos_way[1] -= v
        elif c == "E": pos_way[0] += v
        elif c == "W": pos_way[0] -= v
        elif c == "R": pos_way = rotatePosition( pos_way, +v )
        elif c == "L": pos_way = rotatePosition( pos_way, -v )
        else:
            print("ratiei: " + c)
            exit()

    return abs(pos[0]) + abs(pos[1])
if __name__ == '__main__':
    inp = [ (s[0], int(s[1:])) for s in map( lambda x: x.strip(), sys.stdin.readlines() ) ]

    print("Part 1: %d" % (part1(inp)) )
    print("Part 2: %d" % (part2(inp)) )
