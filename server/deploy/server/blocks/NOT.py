#SolverPath=./blocks/NOT.py
#GivenVars=x
#SolvedVars=f
#Name=NOT
#Description=Returns logical NOT operation
#AuthorName=Adefe
#Color=16768220
#Python block config end

import sys
import math

def main():
    a = float(sys.argv[1])
    res = 1
    if a == 1:
        res = 0
    print(res, sep=' ', end='')


if __name__=='__main__':
    main();

