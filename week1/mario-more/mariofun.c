#include <cs50.h>
#include <stdio.h>

void printer (int y , char text ){
for(int i=0 ; i < y ; i++){
    printf("%c",text);
}
}

int main (void){
    int rows;
    do{
    rows = get_int("rows: ");
    } while (rows >8 || rows <0 );

    for(int i =0 ; i <= rows ; i++){
        printer(rows-i ,' ');
        printer(i,'#');
        printer(1,' ');
        printer(i,'#');
        printer(1 ,'\n');
    }
}