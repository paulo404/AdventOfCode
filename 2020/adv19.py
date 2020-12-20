#!/usr/bin/env python3
import sys
from parse import parse

def apply_rule( m, cr, rules ) :
    if len(cr) == 0 : return m
    if len(m) == 0 : return False

    e = cr.pop()
    if type(e) == str :
        return apply_rule(m[1:],cr,rules) if m.startswith(e) else False
    else :
        for r in rules[e] :
            rl = list(reversed(list(r)))
            if not (res := apply_rule(m,cr+rl,rules)) == False: return res

    return False

def p1( rules,msgs ) :
    return sum([ 1 if '' == apply_rule(m,[0],rules) else 0 for m in msgs ])

if __name__ == '__main__' :
    rules, msgs = {}, []

    #parsee
    for line in sys.stdin :
        line = line.strip()
        if ':' in line :
            rsep = line.index(':')
            rid = int(line[:rsep])
            if c := parse(' "{}"', line[rsep+1:]) :
                rules[rid] = [c[0]]
            else :
                subrules = line[rsep+1:].split('|')
                rules[rid] = [ [int(x) for x in sr.split()] for sr in subrules]
        elif len(line) > 0 :
            msgs.append(line.strip())

    print( f"Part 1: {p1(rules,msgs)}" )
    rules[8] = [ [42], [42, 8] ]
    rules[11] = [ [42,31], [42,11,31] ]
    print( f"Part 1: {p1(rules,msgs)}" )
