#include <cs50.h>
#include <stdio.h>
void loop (int x , char c){
    int i;
    for (i=0; i < x ; i++){
        printf("%c", c );
    }
}
int main (void) {
   int num = get_int("num:");
   int i;
   int x;
   for (x=1; x<=num ; x++)
   {
    loop(num-x , ' ');
    loop(x , '#');
    loop( 2 , ' ');
    loop(x ,'#');
    printf("\n");

   }
}

