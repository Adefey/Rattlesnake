import json

def main():
    data = {'c':14565, 'd':6}
    result = json.dumps(data)
    print(result)


if __name__=='__main__':
    main();
