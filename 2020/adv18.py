#!/usr/bin/env python3
import sys
import operator

def is_op( op ) :
    return op == operator.add or op == operator.mul

def evalExp( exp, mul_lower_precedence):
    s = []
    sexp = range(len(exp))
    for i in  sexp:
        c = exp[i]
        # add char to stack
        if   c == '(' : s.append(c)
        elif c == '*' : s.append(operator.mul)
        elif c == '+' : s.append(operator.add)
        elif c == ')' : s = s[:-2] + [s[-1]]
        else          : s.append(int(c)) #only 1 digit numbers

        # apply operator
        while len(s) >= 3 and '(' not in s[-3:] :
            op1, f, op2 = s[-3:]
            if not is_op(f) : break
            if mul_lower_precedence :
                if f == operator.mul and i+1 in sexp and exp[i+1] == '+' : break #* and lookahead is +
            s = s[:-3] + [f(op1, op2)]

    return s[0]
def sumExps( inp , mul_lower_precedence=False ):
    return sum([ evalExp(e, mul_lower_precedence) for e in inp ])

if __name__ == '__main__':
    #remove all whitespaces
    inp = [ x.strip().replace(" ","") for x in sys.stdin.readlines() ]

    print( "Part 1: %d" % ( sumExps(inp)) )
    print( "Part 2: %d" % ( sumExps(inp, True)) )
