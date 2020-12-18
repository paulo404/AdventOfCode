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

def part1conv(init, steps) :
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


def part2conv(init, steps) :
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

def part1(init, steps) :

    np.set_printoptions(threshold=sys.maxsize)
    steps += 1 #extra padding when looking at neighbors
    #create mat m
    growth = steps * 2 #grows in both directions
    shape = tuple( np.array( init.shape ) + growth )
    m = np.zeros( (1+growth, *shape), dtype=np.int16 )

    #insert init in the middle of m
    middle = tuple( np.array( m.shape ) // 2 )
    m[middle[0]] = np.pad( init, (steps,) )

    #if using convalution
    #for i in range(steps) :
    #    m = step(m)

    #DONE pad 1 more?

    #print( m )
    for i in range(steps-1):
        nm = np.zeros( m.shape )
        s = m.shape
        for d in range(1,s[0]-1):
            for r in range(1,s[1]-1):
                for c in range(1,s[2]-1):
                    e = m[d,r,c]
                    #print( f'pos{d,r,c}' )
                    neighm = m[d-1:d+2, r-1:r+2, c-1:c+2]
                    if neighm.shape != (3,3,3):
                        print( neighm.shape )
                        exit()
                    #print( neighm )
                    neigh = neighm.sum() - e
                    ans = 0
                    if e == 1 :
                        if neigh == 3 or neigh == 2 : ans = 1
                    else :
                        if neigh == 3 : ans = 1
                    nm[d,r,c] = ans
        #print( f'step: {i}' )
        #print( nm )
        m = nm

    return m.sum()


def part2(init, steps) :

    steps += 1 #extra padding when looking at neighbors
    #create mat m
    growth = steps * 2 #grows in both directions
    shape = tuple( np.array( init.shape ) + growth )
    m = np.zeros( (1+growth, 1+growth, *shape), dtype=np.int16 )

    #insert init in the middle of m
    middle = tuple( np.array( m.shape ) // 2 )
    m[middle[0],middle[1]] = np.pad( init, (steps,) )

    for i in range(steps-1):
        nm = np.zeros( m.shape )
        s = m.shape
        for z in range(1,s[0]-1):
            for d in range(1,s[1]-1):
                for r in range(1,s[2]-1):
                    for c in range(1,s[3]-1):
                        e = m[z,d,r,c]
                        #print( f'pos{d,r,c}' )
                        neighm = m[z-1:z+2,d-1:d+2, r-1:r+2, c-1:c+2]
                        neigh = neighm.sum() - e
                        ans = 0
                        if e == 1 :
                            if neigh == 3 or neigh == 2 : ans = 1
                        else :
                            if neigh == 3 : ans = 1
                        nm[z,d,r,c] = ans
        m = nm

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
