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
void * start_slot(void * arg);
void *mix_array(int num, char *chars);
void *user_interface(void *a);

char temp[ARRAY_SIZE];
pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;



int main(){
  int status;
  int f_th = 1;
  int s_th = 3;
  int th_th = 5;
  
  pthread_t first_slot, second_slot, third_slot, user_thread;

  status = pthread_create(&first_slot, NULL, &start_slot, &f_th);
  if (status)
    {
      fprintf(stderr, "ERROR: pthread_create %d\n", status);
      exit(EXIT_FAILURE);
    }
  printf("Created new thread \n");
  
  status = pthread_create(&second_slot, NULL, &start_slot, &s_th);
  if (status)
    {
      fprintf(stderr, "ERROR: pthread_create %d\n", status);
      exit(EXIT_FAILURE);
    }
  printf("Created new thread \n");
  status = pthread_create(&third_slot, NULL, &start_slot, &th_th);
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


void * start_slot(void * arg){
  int num = *((int *)arg);
  //printf("num  %d\n", num);
  
  
  char chars[] = {'M', 'A', 'R', 'G', 'O', 'T'};
  
  if(num < 5 && num > 0){
    // Lock before the critical section
    pthread_mutex_lock(&mutex_1);
    mix_array(num, chars);
    // Unlock after the task is completed
    pthread_mutex_unlock(&mutex_1);
  }else if (num >= 20){
    for(int i = 0; i < ARRAY_SIZE; i++){
      printf("%c", chars[i]);
    }
    num = 1;
    user_interface(&num);
  }
  
  
  return NULL;
}

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
    temp[i] = chars[x];
  }
  for(int i = 0; i < ARRAY_SIZE; i++){
    chars[i] = temp[i];
  }
  
}

void *user_interface(void *a){
  int option;
  printf("press \n -1 to stop the game \n 21 (our lucky unmber) to watch your slots ");
  scanf("%d", &option);
  start_slot(&option);
}
