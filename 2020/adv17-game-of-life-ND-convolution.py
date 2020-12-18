#!/usr/bin/env python3
import numpy as np
import sys

def apply_rule(neigh,m) :
    return 1 if neigh == 3 or (neigh == 2 and m == 1) else 0

#n-d convolution and game of life
def step(m, dim) :
    #sum_conv - m ==> each pos holds its number of neighbors

    #convolution
    # https://stackoverflow.com/q/43086557
    kernel = np.ones( (3,) * dim , dtype=np.int16 )
    #ignore itself
    kernel[ tuple( np.array(kernel.shape) // 2 ) ] = 0
    # calc the size of the array of submatracies
    sub_shape = tuple(np.subtract(m.shape, kernel.shape) + 1) + kernel.shape

    # alias for the function
    strd = np.lib.stride_tricks.as_strided
    # make an array of submatracies
    submatrices = strd(m, sub_shape, m.strides * 2)

    # sum the submatraces and kernel
    nm = submatrices * kernel
    last_axes = tuple( (np.arange(dim) + 1) * -1 )
    nm = nm.sum(axis=last_axes)

    #pad to original size
    nm = np.pad( nm, (1,) )

    #apply game of life rules
    rule = np.vectorize(apply_rule)
    return rule( nm, m )

def part1(init, steps) :
    #create mat m
    growth = steps * 2 + 2 #grows in both directions ( must be bigger than last size )
    shape = tuple( np.array( init.shape ) + growth )
    m = np.zeros( (1+growth, *shape), dtype=np.int16 )

    #insert init in the middle of m
    middle = tuple( np.array( m.shape ) // 2 )
    m[middle[0]] = np.pad( init, (steps+1,) )

    for i in range(steps) :
        m = step(m,3)
    return m.sum()


def part2(init, steps) :
    #create mat m
    growth = steps * 2 + 2 #grows in both directions ( must be bigger than last size )
    shape = tuple( np.array( init.shape ) + growth )
    m = np.zeros( (1+growth,1+growth, *shape), dtype=np.int16 )

    #insert init in the middle of m
    middle = tuple( np.array( m.shape ) // 2 )
    m[middle[0],middle[1]] = np.pad( init, (steps+1,) )

    for i in range(steps) :
        m = step(m,4)
    return m.sum()

if __name__ == '__main__':
    inp = [ s.strip() for s in sys.stdin.readlines() ]

    #transform into matrix
    row, col = len(inp), len(inp[0])
    init = np.zeros( (row,col), dtype=np.int16 )
    for r in range(row):
        for c in range(col):
            if inp[r][c] == '#': init[r,c] = 1

    print( f"Part 1: {part1conv(init,6)}")
    print( f"Part 2: {part2conv(init,6)}")
