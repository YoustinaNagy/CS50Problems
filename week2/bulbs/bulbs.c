#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    string message = get_string("Message: ");
    for(int i=0; message[i] != '\0' ; i++){
       int num = message[i];
      // printf("%c",message[i]);
        for(int x=7; x> -1 ; x-=1)
        {
            int bit  = (num /pow(2, x));
         // printf("num= %i x= %i bit= %i\n",num,x,bit);
            if (bit == 0)
               {
                  // Dark emoji
                  printf("\U000026AB");
               }
            else if (bit == 1)
            {
                  // Light emoji
                  printf("\U0001F7E1");
                  num -= (pow(2, x));
            }
       }
     printf("\n");
  }

}
