#include <cs50.h>
#include <stdio.h>
void rec (int num);
int main (void){
    rec(3);
    }
void rec (int num){
    if(num == 0){
        return;
    }
    for(int i=0;i<num;i++){
        printf("#");
    }
    printf("\n");
    rec(num -1);
}
