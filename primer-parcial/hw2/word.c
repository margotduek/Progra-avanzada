/*
Margot Duek Kalach 
Advanced programming 
Word finder 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SENTENCE 100
#define WORD 10

int count(char *word, char *sentence, int size_word, int size_sentence);
int getInput(char *question, char *inputBuffer, int bufferLength);


int main(){
  char sentence[SENTENCE];
  char word[WORD];

  // Ask the user for a sentence and a word
  int s_size = getInput("Hello!\n give me a sentence:  ", sentence, SENTENCE);
  int w_size = getInput("give me the word you want to look for in the sentence:  ", word, WORD);

  count(word, sentence, w_size, s_size);
  
  return 0;
}


//  Function get an input and know the length  
int getInput(char *question, char *inputBuffer, int bufferLength)
{
  printf("%s  (Max %d characters)\n", question, bufferLength - 1);
  fgets(inputBuffer, bufferLength, stdin);
  int leng = 0;
  // If there is an enter, return the length of the string 
  for(int i = 0; i < bufferLength; i++){
    if(inputBuffer[i] != '\n'){
      leng ++;
    }else if(inputBuffer[i] == '\n'){
      break;
    }
  }
  if (inputBuffer[strlen(inputBuffer) -1] != '\n'){
    int dropped = 0;
    while (fgetc(stdin) != '\n'){
      dropped++;
    }
    printf("%d", dropped);
    if (dropped > 0){ // if they input exactly (bufferLength - 1)
      // characters, there's only the \n to chop off
      printf("Woah there partner, your input was over the limit by %d characters, try again!\n", dropped );
      getInput(question, inputBuffer, bufferLength);
	
    }
  }
  else{
      inputBuffer[strlen(inputBuffer) -1] = '\0';
  }
  return leng;
}


//Function to check how many times a word is in a sentence
int count(char *word, char *sentence, int size_word, int size_sentence){
  int i;
  int words = 0;
  int letters = 0;
  // We loop through the sentence to look for the word 
  for(i = 0; i < size_sentence; i++){
    if(*(sentence+i) == word[0]){
      int j;
      for(j = 0; j < size_word; j++){
	if(*(sentence+i+j) == word[j]){
	  letters ++;
	}
      }
      if(letters == size_word){
	words ++;
      }
      letters = 0;
    }
  }
  printf("Your sentence have %d times that word", words);
  return words;
}
