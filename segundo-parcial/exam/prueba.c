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
char chars1[] = {'M', 'A', 'R', 'G', 'O', 'T'};  
char chars2[] = {'M', 'A', 'R', 'G', 'O', 'T'};
char chars3[] = {'M', 'A', 'R', 'G', 'O', 'T'};
int f_th = 1;
int s_th = 3;
int th_th = 5;


int main(){
  int status;
  
  pthread_t first_slot, second_slot, third_slot, user_thread;

  status = pthread_create(&first_slot, NULL, &start_slot1, &f_th);
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


void * start_slot1(void * arg){
  int num = *((int *)arg);
  //  while(num > 0){
    // Lock before the critical section
    pthread_mutex_lock(&mutex_1);
    mix_array(num, chars1);
    // Unlock after the task is completed
    pthread_mutex_unlock(&mutex_1);
    for(int i = 0; i < ARRAY_SIZE; i++){
      printf("|  %c  | \n", chars1[i]);
    }

    //}
  return NULL;
}

    /*
    if(x >= ARRAY_SIZE - 1){
      x = x - ARRAY_SIZE -1;
    }else if( x < ARRAY_SIZE){
      x = i;
    }
    */


void *mix_array(int num, char *chars){
  int x;
  for(int i = 0; i < ARRAY_SIZE*num ; i+num){

    if( x < ARRAY_SIZE){
      x = i;
    }
    else if (x >= ARRAY_SIZE - 1){
      x = 
    }else if(x < ARRAY_SIZE && !restarted){
      x = i + num;
    }
    temp[i] = chars[x];
  }
  for(int i = 0; i < ARRAY_SIZE; i++){
    chars[i] = temp[i];
  }

}
