import sys
import numpy as np

def part1( inp ):
    pos, orient = (0+0j), (1+0j)
    directions = {"N": 0 + 1j, "E": 1 + 0j, "S": 0 - 1j, "W": -1 + 0j}

    for c,v in inp:
        if   c == "F": pos    += orient * v
        elif c == "R": orient *= (-1j) ** (v//90)
        elif c == "L": orient *= (+1j) ** (v//90)
        else:          pos    += directions[c] * v

    return abs(pos.real) + abs(pos.imag)

def part2( inp ):
    way_pos, way_orient = (10+1j), (1+0j)
    pos = (0+0j)
    directions = {"N": 0 + 1j, "E": 1 + 0j, "S": 0 - 1j, "W": -1 + 0j}

    for c,v in inp:
        if   c == "F": pos        += way_pos * v
        elif c == "R": way_pos    *= (-1j) ** (v//90)
        elif c == "L": way_pos    *= (+1j) ** (v//90)
        else:          way_pos    += directions[c] * v

    return abs(pos.real) + abs(pos.imag)

if __name__ == '__main__':
    inp = [ (s[0], int(s[1:])) for s in [ x.strip() for x in sys.stdin.readlines() ] ]

    print("Part 1: %d" % (part1(inp)) )
    print("Part 2: %d" % (part2(inp)) )
