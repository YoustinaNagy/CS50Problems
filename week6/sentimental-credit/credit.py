# TODO
from cs50 import get_string,get_int

def main():
    num=get_string("number: ")
    # //american express

    # if num%(pow(10,13)) in [34,37] :#and check(num)=="true":
    if len(num)==15 and num[0] == '3' and (num[1] == '4' or num[1] == '7') and check (num):
        print("AMEX")


    # //master
    # elif num%(pow(10,14)) in range(51,56,1):# and check(num)=="true":
    elif (len(num) ==16) and (num[0]=='5') and (int(num[1])in range(6))and check (num):
        print("MASTERCARD")

    # //visa
    # elif 4 in [(num%(pow(10,12))),(num%(pow(10,15)))] :#and check(num)=="true":
    elif (len(num) in [13,16]) and (num[0]=='4')and check (num):
        print("VISA")
    else:
        print("INVALID")
        # print(num[0])
        # print(num[1])
        # print(len(num))
        # print(int(num)%(pow(10,11)))
        # last=2.7
        # print(last)
        # print(int(last))
        # check(num)


def check(num):
    sum=0
    for i in range  (len(num) - 2, -1 , -2):
        # print('debgging 1:', num[i])
        x=int(num[i])*2
        if x//10 > 0:
            sum+=(x%10+1)
        else:
            sum+=x
        # print('debuggin 2:', sum)
    for i in range  (len(num) - 1, -1, -2):
        # print('debugging 3:', num[i])
        sum+=int(num[i])
        # print('debugging 4:', sum)
    # print(sum)
    return sum%10 == 0


    # last = sum%10
    # if (last % (int(last))==0):
    #     # print("true")
    #     return 0
    # else:
    #     # print("false")
    #     return 1

main()