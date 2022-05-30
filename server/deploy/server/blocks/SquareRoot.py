#SolverPath=./blocks/SquareRoot.py
#GivenVars=a
#SolvedVars=sqrt
#Name=SquareRoot
#Description=Returns the square root of number
#AuthorName=Adefe
#Color=14483420
#Python block config end

import sys
import math

def main():
    a = float(sys.argv[1])
    print(math.sqrt(a), sep=' ', end='')

if __name__=='__main__':
    main();

