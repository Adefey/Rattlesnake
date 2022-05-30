#SolverPath=./blocks/Division.py
#GivenVars=a b
#SolvedVars=div
#Name=Division
#Description=Returns number devided by another number
#AuthorName=Adefe
#Color=14483420
#Python block config end

import sys
import math

def main():
    a = float(sys.argv[1])
    b = float(sys.argv[2])
    print(a/b, sep=' ', end='')


if __name__=='__main__':
    main();

