import json
import sys

def main():
    res = int(sys.argv[1]); #FirstBlock_alpha
    SecondBlock_alpha = res  / 1000;
    print(SecondBlock_alpha, sep=' ', end='')

if __name__=='__main__':
    main();
