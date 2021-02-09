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
  symbols->darr = (char*) malloc(sizeof(char) * (symbols->size + 4));

  for (int i = 0; i < symbols->size; i++) {
    symbols->darr[i] = temp[i];
  }
  symbols->size += 4;
}

bool is_empty(stack* symbols) {
  bool hasElements = false;
  int i = symbols->top;

  while (i >= 0) {
    if (symbols->darr[i] != '\0') {
      hasElements = true;
      break;
    }
    i--;
  }
  return !hasElements;
}

void push(stack* symbols, char newVal) {
  if (symbols->size - 1 == symbols->top) {
    grow(symbols);
  }

  symbols->darr[symbols->top +1] = newVal;
  symbols->top++;
}


void pop(stack* symbols) {

}

void clear(stack* symbols) {
  free(symbols->darr);
  init(symbols);
}

int processInput(stack* symbols, char* input) {
  size_t i = 0;
  bool siblingFound;
  while (input[i] != '\0') {
    printf("input[i]: %c ", input[i]);
    
    if (
      input[i] == '(' ||
      input[i] == '{' ||
      input[i] == '[' ||
      input[i] == '<') {

    } else if (
      input[i] == ')' ||
      input[i] == '}' ||
      input[i] == ']' ||
      input[i] == '>') {

    }

    i++;
  }
  printf("\n");
  return 0;
}

int main (int argc, char** argv) {
  stack symbols;
 char input[301];
 int result;

  init(&symbols);
  printf("symbols.size %d\n", symbols.size);

  if (is_empty(&symbols)) {
    printf("symbols is empty\n");
  } else {
    printf("symbols is not empty\n");
  }
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
   result = processInput(&symbols, input);

   /* run the algorithm to determine is input is balanced */
   clear(&symbols);
 }

 free(symbols.darr);
 printf ("\nGoodbye\n");
 return 0;
}

