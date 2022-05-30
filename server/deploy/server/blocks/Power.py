#SolverPath=./blocks/Power.py
#GivenVars=a b
#SolvedVars=pow
#Name=Power
#Description=Returns the number A in power B
#AuthorName=Adefe
#Color=14483420
#Python block config end

import sys
import math

def main():
    a = float(sys.argv[1])
    b = float(sys.argv[2])
    print(math.pow(a, b), sep=' ', end='')

if __name__=='__main__':
    main();

