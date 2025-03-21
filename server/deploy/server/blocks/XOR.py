#SolverPath=./blocks/XOR.py
#GivenVars=x y
#SolvedVars=f
#Name=XOR
#Description=Returns logical XOR operation
#AuthorName=Adefe
#Color=16768220
#Python block config end

import sys
import math

def main():
    a = float(sys.argv[1])
    b = float(sys.argv[2])
    res = 0
    if (a!=b) and (a+b!=0):
        res = 1

    print(res, sep=' ', end='')


if __name__=='__main__':
    main();
