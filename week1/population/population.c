#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    int end;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);


    // TODO: Prompt for end size
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);


    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (end > start){
        start= start+(start/3)-(start/4);
        years=years+1;
    }


    // TODO: Print number of years
    printf("Years: %i\n", years);
}
