#SolverPath=./blocks/IMPLY.py
#GivenVars=x y
#SolvedVars=f
#Name=IMPLY
#Description=Returns logical IMPLICATION operation
#AuthorName=Adefe
#Color=16768220
#Python block config end

import sys
import math

def main():
    a = float(sys.argv[1])
    b = float(sys.argv[2])
    res = 1
    if (a!=0) and (b==0):
        res = 0

    print(res, sep=' ', end='')


if __name__=='__main__':
    main();
