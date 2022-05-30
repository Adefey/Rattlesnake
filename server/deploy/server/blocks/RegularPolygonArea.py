#SolverPath=./blocks/RegularPolygonArea.py
#GivenVars=r_outer n_sides
#SolvedVars=area
#Name=RegularPolygonArea
#Description=Returns area of the regular polygon by its outer circle radius and sides count
#AuthorName=Adefe
#Color=14474495
#Python block config end

import sys
import math

def main():
    r = float(sys.argv[1])
    n = float(sys.argv[2])
    res = 1/2*(r**2)*n*math.sin((2*math.pi)/n)
    print(res, sep=' ', end='')


if __name__=='__main__':
    main();



