#include <cs50.h>
#include <stdio.h>
#include <string.h>
//letters

 int count_letters(string text){
   int text_length = strlen(text);
   int letters = 0 ;
      for (int i = 0; i < text_length; i++){
      if(text[i]> 64 && text[i] < 123 ){
        letters +=1 ;
        }
      }
    return letters ;
}

    //words
  int count_words(string text){
   int i;
   int words = 1 ;
      for(i=0; text[i] != '\0' ; i++){
      if(text[i] == ' '){
        words +=1 ;
        }
      }
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
int main(void)
{
    string text = get_string("Text:");
    // string text ="When he was nearly thirteen, my brother Jem got his arm badly broken at the elbow. When it healed, and Jem's fears of never being able to play football were assuaged, he was seldom self-conscious about his injury. His left arm was somewhat shorter than his right; when he stood or walked, the back of his hand was at right angles to his body, his thumb parallel to his thigh.";
    // printf("letters = %i \n" , count_letters(text));
    // printf("word = %i \n" , count_words(text));
    // printf("sentence = %i \n" , count_sentence(text));
float index = (0.0588 * count_letters(text) / count_words(text) * 100) - (0.296 * count_sentence(text) / count_words(text) * 100) - 15.8; // to calculate Index
    // float L = (count_letters(text) / count_words(text))*100;
    // float S = (count_sentence(text) / count_words(text))*100;
    // float index = 0.0588 * L - 0.296 * S - 15.8 ;
    int index2 = index ;
    float x= index - (float)index2;
    // printf("%f /n", x);
    if((index - index2)>= 0.5){
        index2 +=1;
        // printf("index= %f \n", index);
        // printf("index2=%i \n",index2);
    }

    if(index2 > 15){
        printf("Grade 16+\n");
    }
    else if( index2 < 1 ){
      printf("Before Grade 1\n");
    }
    else{
      printf("Grade %i\n", index2);
    }
}