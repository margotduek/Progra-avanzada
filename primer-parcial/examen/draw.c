
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Draw the line showing the progress of the counts
// Called at every loop
// Will modify the string, adding '\' characters from the left
//  and '/' characters fromt he right. 'X' characters are used
//  when the counts intersect.
// Use only pointer arithmetic to modify the string
// Receives: the string, the size, and the counters for left and right
// Return: nothing

     
void fill_line(char *line, int range){
  for(int i = 0; i < range; i++){
    *(line + i) = ' ';
  }
}

void drawLine(char * line, int range, int count_up, int count_down)
{
  line = (char *) malloc(sizeof(char)*range);

  fill_line(line, range);
 
    for(int i = 0; i < count_up ; i++){
      *(line + i) = '\\';
    }
    for(int i = 0; i < count_down ; i++){
      if(*(line + (range - i)) == '\\'){
	*(line + (range - i)) = 'X';
      }else{
	*(line + (range - i)) = '/';
      }
    }

  printf("%s\n", line);
}
 


int main(){
  char *line = NULL;

  drawLine(line, 10, 1, 2);
  drawLine(line, 10, 2, 3);

  drawLine(line, 10, 3, 4);

  drawLine(line, 10, 4, 5);
  drawLine(line, 10, 5, 6);
  drawLine(line, 10, 6, 7);

  drawLine(line, 10, 7, 8);

  drawLine(line, 10, 8, 9);


  drawLine(line, 10, 9, 10);

  drawLine(line, 10, 10, 10);  
  return 0;
}
