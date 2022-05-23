import json
import sys

def main():
    a = float(sys.argv[1]);
    res = a  / 1000;
    print(res, sep=' ', end='')

if __name__=='__main__':
    main();
