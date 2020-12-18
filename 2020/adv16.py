#!/usr/bin/env python3
import sys
from parse import parse
from itertools import chain

def part1( fields, tickets ):
    all_ranges = list(chain(*fields.values()))
    error_rate, valid_tickets = 0, []
    for t in tickets:
        valid = True
        for v in t:
            if True not in [ v in r for r in all_ranges ]:
                error_rate += v
                valid = False
                break
        if valid: valid_tickets.append(t)
    return error_rate, valid_tickets


def part2( fields, tickets, my_ticket):
    possible_indexes = {}
    remaining_fields = list(range(len(tickets[0])))

    #for all fields
    for fname,rs in fields.items():
        #try to find among the remaining fields
        for f in remaining_fields:
            #if all values
            all_valid = True
            for v in [ tickets[i][f] for i in range(len(tickets)) ]:
                # are in the accepted values
                if True not in [ v in r for r in rs ]:
                    all_valid = False

            if all_valid:
                if fname in possible_indexes:
                    possible_indexes[fname].append(f)
                else:
                    possible_indexes[fname] = [f]

    #find one to one mapping from fields to their positions
    remaining = list(possible_indexes.items())
    d = {}
    while True:
        remaining.sort(key= lambda x: len(x[1]))
        if len(remaining[0][1]) > 1: raise Exception('fudeu')
        first = remaining.pop(0)
        fname, index = first[0], first[1][0]
        d[fname] = index
        if len(remaining) == 0: break
        for i in range(len(remaining)):
            if index in remaining[i][1]:
                remaining[i][1].remove(index)

    prod = 1
    for k,v in d.items():
        if k.startswith("departure"): prod *= my_ticket[v]
    return prod
if __name__ == '__main__':

    #fields
    inp = sys.stdin.readlines()
    fields_end_ind = inp.index("\n")
    fields = { k:[range(v[0],v[1]+1), range(v[2],v[3]+1)] for k,*v in [ parse("{}: {:d}-{:d} or {:d}-{:d}\n", s ) for s in inp[:fields_end_ind] ] }

    #tickets
    inp = inp[fields_end_ind+2:]
    my_ticket = [ int(x) for x in inp[0].split(',') ]

    inp = inp[3:]
    tickets = [ [ int(x) for x in t.split(',') ] for t in inp ]

    ans1, tickets = part1( fields, tickets)
    print( "Part 1: %d" % ( ans1 ) )
    print( "Part 2: %d" % ( part2( fields, tickets, my_ticket ) ) )
