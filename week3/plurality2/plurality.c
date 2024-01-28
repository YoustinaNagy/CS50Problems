#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9
// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(int voter_count , int x,string winner,string winner2);
int score(string name);
bool equal(int x ,int voter_count );

int main(int argc, string argv[])
{

    string winner =candidates[0].name;
    string winner2=candidates[0].name;;
    int x=0;
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (argc > 10)
    {
        printf("Maximum number of candidates is 9\n");
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");
       if (vote(name) == false )
        {
            printf("Invalid vote.\n");
        }else{  //add to score if its valid input
           candidates[score(name)].votes +=1;
        }

     }
     print_winner(voter_count ,x,winner, winner2);

}

bool equal(int x ,int voter_count )
   {
    for(int i=voter_count-x-1;i<voter_count-1;i++){
            if(candidates[i].votes < candidates[i+1].votes){

              return false;
            }

            }
           return true;
   }



bool vote(string name)
{
    for(int i = 0; i < candidate_count; i++)
        if (strcmp(candidates[i].name ,name) == 0)
        {
           return true;
        }
    return false;
}
int score(string name)
{
    for(int i = 0; i < candidate_count; i++)
        if (strcmp(candidates[i].name ,name) == 0)
        {
           return i;
        }
    return -1;
}



// Print the winner (or winners) of the election
void print_winner(int voter_count , int x,string winner,string winner2)
{
     if(x<voter_count-1){
            if(candidates[x].votes > candidates[x+1].votes){
                candidates[x+1].name=candidates[x].name;
                candidates[x+1].votes=candidates[x].votes;
                winner = candidates[x+1].name;
            }
            else if(candidates[x].votes < candidates[x+1].votes)
            {
                winner = candidates[x+1].name;
            }
            else if((candidates[x].votes)==(candidates[x+1].votes) && (equal(x,voter_count)==true) )
            {
                winner = candidates[x].name;
                winner2 = candidates[x+1].name;
                printf("%s\n%s\n",winner,winner2);
                return;
            }
       x+=1;
      print_winner(voter_count ,x,winner, winner2);
     }
 printf("%s\n",winner);
 return;
}