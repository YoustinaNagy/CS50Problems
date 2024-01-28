#include <cs50.h>
#include <stdio.h>
   //letters
 int count_letters(string text){
   int i;
   int letters = 0 ;
      for(i=0; text[i] != '\0' ; i++){
      if(text[i]> 64 && text[i] < 123 ){
        letters +=1 ;
        }
      }
    return letters ;
}

    //words
  int count_words(string text){
   int i;
   int words = 0 ;
      for(i=0; text[i] != '\0' ; i++){
      if(text[i] == ' '  && text[i+1] != ' '  && text[i+1] != ';'){
        words +=1 ;
        }
      }
      words +=1 ;
    return words ;
}

 //Sentences
  int count_sentence(string text){
   int i;
   int sentence = 0 ;
      for(i=0; text[i] != '\0' ; i++){
      if(text[i] == '.'  || text[i] == '!'  || text[i] == '?'){
        sentence +=1 ;
        }
      }
      return sentence ;
}

int main (void){

    //string text = get_string("Text:");
    string text ="One fish. Two fish. Red fish. Blue fish.";
    //printf("letters = %i \n" , count_letters(text));
    //printf("word = %i \n" , count_words(text));
    //printf("sentence = %i \n" , count_sentence(text));
    int L = (count_letters(text) / count_words(text))*100;
    int S = (count_sentence(text) / count_words(text))*100;
    int index = 0.0588 * L - 0.296 * S - 15.8 ;
    if(index > 15){
        printf("Grade 16+");
    }
    else if( index < 1 ){
      printf("Before Grade 1");
    }
    else{
      printf("Grade %i", index);
    }
   
}