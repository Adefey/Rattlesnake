import json
import sys
import time

def main():
    a = float(sys.argv[1]);
    b = float(sys.argv[2]);
    res1 = a * 10;
    res2 = b / 10;
    print(res1, res2, sep=' ', end='')


if __name__=='__main__':
    main();
