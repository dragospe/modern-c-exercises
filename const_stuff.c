#include <stdio.h>


void f(char* x){
  printf("Before dereferencing const.\n");
  &x;
  printf("After dereferncing const.\n");
  *x = 'l';
}

int main(void){
  char* l;
  l[0] = 'a';
  l[1] = 'b';
  l[2] = 'c';
  l[3] = '\000';
  printf("%s\n",l);
  f(l);
  printf("%s\n",l);
}


// Works with char x[], x[0], char l[3]
// Works with char* x, *x
// Does not work with char*
