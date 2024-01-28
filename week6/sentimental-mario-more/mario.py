# TODO
def main():
    num = get_positive()
    for i in range(num):
        printer(' ',(num-i-1))
        printer('#',(i+1))
        printer(' ',2)
        printer('#',(i+1))
        print()

def get_positive():
    while True:
        try:
            num = int(input("Height: "))
            if (num > 0) and (num < 9):
                break
        except:
            num = int(input("Height: "))
            if (num > 0) and (num < 9):
                break

    return num


def printer(str,num):
    print(str*num,end="")



main()

