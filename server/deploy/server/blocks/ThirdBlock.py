import json
import sys

def main():
    a = float(sys.argv[1]);
    b = float(sys.argv[2]);
    res1 = a  + b;
    res2 = a  - b;
    print(res1, res2, sep=' ', end='')

if __name__=='__main__':
    main();
