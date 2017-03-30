/*
  Margot Duek Kalach 
  Advanced programming 
  A01021226
  Second partial
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define ARRAY_SIZE 6

// Function declarations
void * start_slot1(void * arg);
void * start_slot2(void * arg);
void * start_slot3(void * arg);
void *mix_array(int num, char *chars);
void *user_interface(void *a);

char temp[ARRAY_SIZE];
pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
char chars1[] = {'M', 'G', 'R', 'A', 'O', 'T'};  
char chars2[] = {'R', 'M', 'T', 'A', 'O', 'G'};
char chars3[] = {'O', 'T', 'A', 'R', 'G', 'M'};
int f_th = 1;
int s_th = 3;
int th_th = 5;
int running = 1;

int main(){
  int status;
  
  pthread_t first_slot, second_slot, third_slot, user_thread;

  //we start each thread checking if it was successfully created 
  status = pthread_create(&first_slot, NULL, &start_slot1, &f_th);
  if (status)
    {
      fprintf(stderr, "ERROR: pthread_create %d\n", status);
      exit(EXIT_FAILURE);
    }
  printf("Created new thread \n");
  
  status = pthread_create(&second_slot, NULL, &start_slot2, &s_th);
  if (status)
    {
      fprintf(stderr, "ERROR: pthread_create %d\n", status);
      exit(EXIT_FAILURE);
    }
  printf("Created new thread \n");
  status = pthread_create(&third_slot, NULL, &start_slot3, &th_th);
  if (status)
    {
      fprintf(stderr, "ERROR: pthread_create %d\n", status);
      exit(EXIT_FAILURE);
    }
  printf("Created new thread \n");
  status = pthread_create(&user_thread, NULL, &user_interface, &th_th);
  if (status)
    {
      fprintf(stderr, "ERROR: pthread_create %d\n", status);
      exit(EXIT_FAILURE);
    }
  printf("Created new thread \n");  
  

  // Wait for all other threads to finish
  pthread_exit(NULL);
  
  
  return 0;
}

/*
  All the start_slot functions are running until we have a negative varible to stop 
  the threads. Inside this while we aquire a mutex to use a global array that they 
  can't use ath the same time. Inside the mutex we call the mixing function 
*/

void * start_slot1(void * arg){
  int num = *((int *)arg);
  while(running > 0){
    // Lock before the critical section
    pthread_mutex_lock(&mutex_1);
    mix_array(num, chars1);
    // Unlock after the task is completed
    pthread_mutex_unlock(&mutex_1);
  }
  return NULL;
}

void * start_slot2(void * arg){
  int num = *((int *)arg);
  while(running > 0){
    // Lock before the critical section
    pthread_mutex_lock(&mutex_1);
    mix_array(num, chars2);
    // Unlock after the task is completed
    pthread_mutex_unlock(&mutex_1);
  }
  return NULL;
}

void * start_slot3(void * arg){
  int num = *((int *)arg);
  while(running > 0){
    // Lock before the critical section
    pthread_mutex_lock(&mutex_1);
    mix_array(num, chars3);
    // Unlock after the task is completed
    pthread_mutex_unlock(&mutex_1);
  }
  return NULL;
}

/*
  In this function we are moving the chars around the array 
  with an identifier number that we pass as a parameter to sort in 
  a different way each array
*/
void *mix_array(int num, char *chars){
  int x;
  int restarted = 0;
  for(int i = 0; i < ARRAY_SIZE ; i++){

    if( x < ARRAY_SIZE && restarted){
      x++;
    }
    else if (x >= ARRAY_SIZE - 1){
      x = 0;
      restarted = 1;
    }else if(x < ARRAY_SIZE && !restarted){
      x = i + num;
    }
    //pass the numbers to the temporal array 
    temp[i] = chars[x];
  }
  //Pass the numbers fron the temporal to the slot array 
  for(int i = 0; i < ARRAY_SIZE; i++){
    chars[i] = temp[i];
  }

}


void *user_interface(void *a){
  int option = 0;
  int lines;
  int bet;
  while (option >= 0){
    printf("\n\n press \n -1 to stop the game \n 21 (our lucky unmber) to watch your slots ");
    scanf("%d", &option);
    if(option > 20){
      printf("\n How many lines do you want to play, 1, 2, 3 or 5? \n ");
      scanf("%d", &lines);
      printf("\n How much do you want to bet? \n ");
      scanf("%d", &bet);
      
      pthread_mutex_lock(&mutex_1);      
      for(int i = 0; i < ARRAY_SIZE; i++){
	printf("|  %c  |  %c  |  %c  |\n", chars1[i], chars2[i], chars3[i]);
      }
      int i = 0;
      if(lines == 1){
	if(chars1[i] == chars2[i] && chars2[i] == chars3[i]){
	  printf("--------- TIN TIN TIN ----------- YOU WON!!!!!! ----------\n");
	  printf("\nyou won %d", bet*5);
	}
      }else if(lines == 2){
	if(chars1[i] == chars2[i] && chars2[i] == chars3[i]){
	  printf("\n--------- TIN TIN TIN ----------- YOU WON ON THE FIRST LINE!!!!!! ----------");
	  printf("\nyou won %d", bet*5);
	}
	if(chars1[i+1] == chars2[i+1] && chars2[i+1] == chars3[i+1]){
	  printf(" \n----------- YOU WON ON THE SECOND LINE!!!!!! ----------");
	  printf("\nyou won %d", bet*3);
	}
      }else if(lines == 3){
	if(chars1[i] == chars2[i] && chars2[i] == chars3[i]){
	  printf("\n--------- TIN TIN TIN ----------- YOU WON ON THE FIRST LINE!!!!!! ----------");
	  printf("\nyou won %d", bet*5);
	}
	if(chars1[i+1] == chars2[i+1] && chars2[i+1] == chars3[i+1]){
	  printf("\n ----------- YOU WON ON THE SECOND LINE!!!!!! ----------");
	  printf("\nyou won %d", bet*3);
	}
	if(chars1[i+2] == chars2[i+2] && chars2[i+2] == chars3[i+2]){
	  printf("\n ----------- YOU WON ON THE THIRD LINE!!!!!! ----------");
	  printf("\nyou won %d", bet*2);
	}
      }else if(lines == 5){
	if(chars1[i] == chars2[i] && chars2[i] == chars3[i]){
	  printf("\n--------- TIN TIN TIN ----------- YOU WON ON THE FIRST LINE!!!!!! ----------");
	  printf("\nyou won %d", bet*5);
	}
	if(chars1[i+1] == chars2[i+1] && chars2[i+1] == chars3[i+1]){
	  printf("\n ----------- YOU WON ON THE SECOND LINE!!!!!! ----------");
	  printf("\nyou won %d", bet*3);
	}
	if(chars1[i+2] == chars2[i+2] && chars2[i+2] == chars3[i+2]){
	  printf("\n ----------- YOU WON ON THE THIRD LINE!!!!!! ----------");
	  printf("\nyou won %d", bet*2);
	}
	if(chars1[i] == chars2[i+1] && chars2[i+1] == chars3[i+2]){
	  printf("\n ----------- YOU WON ON THE FIRST CROSS LINE!!!!!! ----------");
	  printf("\nyou won %d", bet*2);
	}
	if(chars1[i+2] == chars2[i+1] && chars2[i+1] == chars3[i]){
	  printf("\n ----------- YOU WON ON THE SECOND CROSS LINE!!!!!! ----------");
	  printf("\nyou won %d", bet*2);
	}
      }
    }
    // Unlock after the task is completed
    pthread_mutex_unlock(&mutex_1);      
  }
  // If the user choose a negative chocice then we stop all the treads and finish the program
  if(option < 0){
    running = option;
  }
}

