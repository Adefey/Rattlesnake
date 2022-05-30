#SolverPath=./blocks/AND.py
#GivenVars=x y
#SolvedVars=f
#Name=AND
#Description=Returns logical AND operation
#AuthorName=Adefe
#Color=16768220
#Python block config end

import sys
import math

def main():
    a = float(sys.argv[1])
    b = float(sys.argv[2])
    res = 1
    if a * b == 0:
        res = 0
    print(res, sep=' ', end='')


if __name__=='__main__':
    main();
