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

void grow(stack* symbols, bool debugMode) {
  int i = 0;
  char* temp;
  temp = symbols->darr;
  symbols->darr = (char*) malloc(sizeof(char) * (symbols->size + 4));
  
  for (i = 0; i < symbols->size; i++) {
    symbols->darr[i] = temp[i];
  }
  if (debugMode) {
    printf(
      "Stack size increased from %d to %d, a total of %d values were copied \n",
      symbols->size,
      symbols->size + 4,
      i);
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

void push(stack* symbols, char newVal, bool debugMode) {
  if (symbols->size - 1 == symbols->top) {
    grow(symbols, debugMode);
  }

  symbols->darr[symbols->top +1] = newVal;
  symbols->top++;
}


char pop(stack* symbols) {
  char val = '\0';
  if (is_empty(symbols)) return val;
  val = symbols->darr[symbols->top];
  symbols->darr[symbols->top] = '\0';
  symbols->top--;
  return val;
}

char top(stack* symbols) {
  char val = '\0';
  if (is_empty(symbols)) return val;
  val = symbols->darr[symbols->top];
  return val;
}

void clear(stack* symbols) {
  free(symbols->darr);
  init(symbols);
}

bool checkSiblingFound(stack* symbols, char inputVal, bool debugMode) {
  if (is_empty(symbols)) return false;
  char topVal = symbols->darr[symbols->top];
  char poppedVal;
  if (
    (inputVal == ')' && topVal == '(') ||
    (inputVal == '}' && topVal == '{') ||
    (inputVal == ']' && topVal == '[') ||
    (inputVal == '>' && topVal == '<')) {
    poppedVal = pop(symbols);
    if (debugMode) printf("Character %c was popped from the stack \n", poppedVal);
    return true;
  }
  return false;
}

char getMissingSymbol(char inputVal) {
  if (inputVal == ')') {
    return '(';
  } else if (inputVal == ']') {
    return '[';
  }  else if (inputVal == '}') {
    return '{';
  }  else if (inputVal == '>') {
    return '<';
  }
  return '\0';
}

char getExpectedSymbol(stack* symbols) {
  char topVal = symbols->darr[symbols->top];
  if (topVal == '(') {
    return ')';
  } else if (topVal == '[') {
    return ']';
  }  else if (topVal == '{') {
    return '}';
  }  else if (topVal == '<') {
    return '>';
  }
  return '\0';
}


int processInput(
  stack* symbols,
  char* input,
  int *problemIndex,
  char *problemChar,
  bool debugMode) {
  size_t i = 0;
  bool siblingFound;
  while (input[i] != '\0') {
    // printf("input[i]: %c ", input[i]);
    *problemIndex = i;
    if (
      input[i] == '(' ||
      input[i] == '{' ||
      input[i] == '[' ||
      input[i] == '<') {
      push(symbols, input[i], debugMode);
      if (debugMode) printf("Character %c was pushed into the stack \n", input[i]);
    } else if (
      input[i] == ')' ||
      input[i] == '}' ||
      input[i] == ']' ||
      input[i] == '>') {
      if (is_empty(symbols)) {
        *problemChar = getMissingSymbol(input[i]);
        return 2;
      }
      siblingFound = checkSiblingFound(symbols, input[i], debugMode);
      if (!siblingFound) {
        *problemChar = getExpectedSymbol(symbols);
        return 1;
      }
    }

    i++;
  }
  // printf("\n");
  if (!is_empty(symbols)) {
    *problemChar = getExpectedSymbol(symbols);
    return 3;
  }
  return 0;
}

void printInputString(char* input) {
  size_t i = 0;
  while (input[i] != '\0') {
    printf("%c", input[i]);
    i++;
  }
  printf("\n");
}

void printResultInfo(char* input, int result, int problemIndex, char problemChar) {
  if (result == 0) {
    printf("Expression is balanced\n");
  } else if (result == 1) {
    printf("Unbalanced expression. Error 1: expecting a different closing symbol\n");
    printInputString(input);
    printf("%*c", problemIndex + 1, '^');
    printf(" expecting %c", problemChar);
  } else if (result == 2) {
    printf("Unbalanced expression. Error 2: missing an opening symbol\n");
    printInputString(input);
    printf("%*c", problemIndex + 1, '^');
    printf(" missing %c", problemChar);
  } else if (result == 3) {
    printf("Unbalanced expression. Error 3: missing a closing symbol\n");
    printInputString(input);
    printf("%*c", problemIndex + 1, '^');
    printf(" missing %c", problemChar);
  }
}

int main (int argc, char** argv) {
  stack symbols;
  char input[301];
  int result;
  int problemIndex;
  char problemChar;
  bool debugMode = false;

  if (argc > 1 && (strcmp(argv[1], "-d") == 0)) {
    debugMode = true;
  }

  init(&symbols);
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
   result = processInput(&symbols, input, &problemIndex, &problemChar, debugMode);
   // printf("problemIndex: %d\n", problemIndex);
   // printf("problemChar: %c\n", problemChar);
   printResultInfo(input, result, problemIndex, problemChar);
   /* run the algorithm to determine is input is balanced */
   clear(&symbols);
 }

 free(symbols.darr);
 printf ("\nGoodbye\n");
 return 0;
}
