import json
import sys

def main():
    a = int(sys.argv[1]);
    b = int(sys.argv[2]);
    FirstBlock_alpha = a * 10;
    FirstBlock_beta = b / 10;
    data = "[{\"param_name\":\"FirstBlock_alpha\",\"param_value\":\""+str(FirstBlock_alpha)+"\"},{\"param_name\":\"FirstBlock_beta\",\"param_value\":\""+str(FirstBlock_beta)+"\"}]"
    print(data)


if __name__=='__main__':
    main();
