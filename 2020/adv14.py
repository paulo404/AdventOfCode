#!/usr/bin/env python3
import sys
import re

def part1( inp ):
    id_and, id_or = 2**64-1, 0
    mem, mask_and, mask_or = {}, id_and, id_or

    for c,*v in inp:
        if c == 'mask':
            mask_and, mask_or = id_and, id_or
            for i,ch in enumerate(reversed(v[0])):
                if ch == '0':   mask_and &= ~(1<<i)
                elif ch == '1': mask_or  |=  (1<<i)
        else:
            mem[v[0]] = v[1] & mask_and | mask_or

    return sum( mem.values() )


def part2( inp ):
    id_and, id_or = 2**64-1, 0
    mem, mask_or, mask_and, floating_bits = {}, id_or, id_and, []

    for c,*v in inp:
        if c == 'mask':
            mask_or, mask_and, floating_bits = id_or, id_and, []
            for i,ch in enumerate(reversed(v[0])):
                if ch == '1': mask_or  |=  (1<<i)
                elif ch == 'X':
                    mask_and &= ~(1<<i) #zero floting bits in mem addr
                    floating_bits.append( i )
        else:
            masked = v[0] & mask_and | mask_or #base addr

            #iterate throught possible values the floating bits could aquire
            for perm in range( 2**len(floating_bits) ):
                f_mask = id_or
                for ib, sa in enumerate(floating_bits):
                    f_mask |=  (1<<ib & perm) >> ib << sa

                mem[ masked | f_mask ] = v[1]

    return sum( mem.values() )

if __name__ == '__main__':
    inp = [ x if x[0] == 'mask' else [x[0], int(x[1]), int(x[2])]
            for x in [ re.compile("[\[\](\s+=\s+)]+").split(s) for s in sys.stdin.readlines() ] ]

    print( "Part 1: %d" % ( part1( inp ) ) )
    print( "Part 2: %d" % ( part2( inp ) ) )
