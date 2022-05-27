#SolverPath=./blocks/CircleArea.py
#GivenVars=radius
#SolvedVars=area
#Name=CircleArea
#Description=Returns area of the circle with the specified radius
#AuthorName=Adefe
#Color=14474495
#Python block config end

import sys
import math

def main():
    r = float(sys.argv[1]);
    area = (r**2) * math.pi;
    print(area, sep=' ', end='')


if __name__=='__main__':
    main();
