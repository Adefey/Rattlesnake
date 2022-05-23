import json
import sys
import time

def main():
    a = int(sys.argv[1]);
    b = int(sys.argv[2]);
    FirstBlock_alpha = a * 10;
    FirstBlock_beta = b / 10;
    print(FirstBlock_alpha, FirstBlock_beta, sep=' ', end='')


if __name__=='__main__':
    main();
