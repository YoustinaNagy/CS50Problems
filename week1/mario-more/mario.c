#include <cs50.h>
#include <stdio.h>

void print(int num, char c)
{
  int i;
  for(i = 1; i <= num; i++) {
  	printf("%c", c);
  }

}

int main(void)
{
  int num;
  do {
    num = get_int("Height: ");
  } while(num < 1 || num > 8);

  int i;
  for(i = 1; i <= num; i++) {
    // this is added for clarity
    print(num - i, ' ');
    print(i, '#');
    print(2, ' ');
    print(i, '#');
    printf("\n");
  }
}