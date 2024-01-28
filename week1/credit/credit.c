#include <cs50.h>
#include <stdio.h>

bool is_valid(long num) {
    int sum = 0;
    bool multiplied = false;
    // 1. loop until the number is zero
    while(num > 0) {
        // 2. get the modulo 10 for the number
        int remainder = num % 10;
        // 3. accumulate number
        if (multiplied == false) {
            sum += remainder;
        } else {
            int temp = remainder * 2;
            sum += temp / 10 + temp % 10;
        }
        // 3. divide the number by 10
        num = num / 10;
        multiplied = !multiplied;
    }
    // printf("total: %d\n", sum);
    if (sum % 10 == 0) {
        return true;
    } else {
        return false;
    }
}

// function getting length
int calc_length(long num) {
    int len = 0;
    while(num > 0) {
        num /= 10;
        len += 1;
    }
    return len;
}

// get the last 2 digits
int get_last_2(long num) {
    while(num > 100) {
        num /= 10;
    }
    return num;
}

int get_last_1(long num) {
    while(num > 10) {
        num /= 10;
    }
    return num;
}

int main(void)
{
    // 1. GET NUMBER
    long num = get_long("Number: ");
    int len = calc_length(num);
    // printf("%ld\n", num);
    // printf("%d\n", len);

    // find visa 13 num
    if (get_last_1(num) == 4 && (len == 13 || len == 16)) {
        if (is_valid(num) == true)
            printf("VISA\n");
        else
            printf("INVALID\n");
    }
    // find express 15 num
    else if (len == 15 &&  (get_last_2(num)==34 || get_last_2(num)==37)) {
        printf("ana hna!!\n");
        if (is_valid(num) == true)
            printf("AMEX\n");
        else
            printf("INVALID\n");
    }
    // visa or master 16
    // else if(len == 16 &&  (get_last_2(num) > 50 && get_last_2(num) < 56)) {
    //     if (is_valid(num) == true)
    //         printf("MASTERCARD\n");
    //     else
    //         printf("INVALID\n");
    // } else {
    //     printf("INVALID\n");
    // }
}