#SolverPath=./blocks/Product.py
#GivenVars=a b
#SolvedVars=prod
#Name=Product
#Description=Returns product of the numbers
#AuthorName=Adefe
#Color=14483420
#Python block config end

import sys
import math

def main():
    a = float(sys.argv[1])
    b = float(sys.argv[2])
    print(a*b, sep=' ', end='')


if __name__=='__main__':
    main();
