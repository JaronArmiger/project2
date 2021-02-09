#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack {
  char* darr;
  int top;
  int size;
} stack;

void init(stack* symbols) {
  symbols->darr = (char*) malloc(sizeof(char) * 4);
  symbols->top = -1;
  symbols->size = 4;
}

void grow(stack* symbols) {
  char* temp;
  temp = symbols->darr;
  symbols->darr = (char*) malloc(sizeof(char) (symbols->size + 4));

  for (int i = 0; i < symbols->size; i++) {
    symbols->darr[i] = temp[i];
  }
  symbols->size += 4;
}

void push(stack* symbols) {
  
}

int main (int argc, char** argv)
{
 char input[301];

 /* set up an infinite loop */
 while (1)
 {
   /* get line of input from standard input */
   printf ("\nEnter input to check or q to quit\n");
   fgets(input, 300, stdin);

   /* remove the newline character from the input */
   int i = 0;
   while (input[i] != '\n' && input[i] != '\0')
   {
      i++;
   }
   input[i] = '\0';

   /* check if user enter q or Q to quit program */
   if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
     break;
 
   /*You can remove/move this print statement based on your code structure */
   printf ("%s\n", input);

   /* run the algorithm to determine is input is balanced */

 }

 printf ("\nGoodbye\n");
 return 0;
}