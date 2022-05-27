#SolverPath=./blocks/EQUAL.py
#GivenVars=x y
#SolvedVars=f
#Name=EQUAL
#Description=Returns logical EQUALITY operation
#AuthorName=Adefe
#Color=16768220
#Python block config end

import sys
import math

def main():
    a = float(sys.argv[1])
    b = float(sys.argv[2])
    res = 0
    if a==b:
        res = 1
    print(res, sep=' ', end='')


if __name__=='__main__':
    main();
