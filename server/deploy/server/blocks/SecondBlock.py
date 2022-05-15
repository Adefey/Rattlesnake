import json
import sys

def main():
    res = int(sys.argv[1]); #FirstBlock_alpha
    SecondBlock_alpha = res + 14565;
    data = "[{\"param_name\":\"SecondBlock_alpha\",\"param_value\":\""+str(SecondBlock_alpha)+"\"}]"
    print(data)

if __name__=='__main__':
    main();
