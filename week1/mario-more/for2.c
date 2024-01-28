#include <cs50.h>
#include <stdio.h>

int main (void){
    int rows = get_int("rows: ");

    for(int i =0 ; i <= rows ; i++){
        for(int space = rows-i-1 ; space>=0 ; space--){
            printf(" ");
        }
        for(int ha4 = 0 ;ha4 <i ; ha4++){
            printf("#");
        }
        printf(" ");
        for(int ha4 = 0 ;ha4 <i ; ha4++){
            printf("#");
        }
        printf("\n");
    }
}