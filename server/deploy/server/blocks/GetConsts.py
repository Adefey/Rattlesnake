#SolverPath=./blocks/GetConsts.py
#GivenVars=
#SolvedVars=pi e g c
#Name=GetConsts
#Description=Returns pi and e numbers, free-fall acceleration and speed of light (SI)
#AuthorName=Adefe
#Color=14474495
#Python block config end

import sys
import math

def main():
    print(math.pi, math.e, 9.8155, 299792458.0, sep=' ', end='')

if __name__=='__main__':
    main();

