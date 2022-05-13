import json

def main():
    data = {'a':1, 'b':2}
    result = json.dumps(data)
    print(result)


if __name__=='__main__':
    main();
