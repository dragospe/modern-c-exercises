#include <stdio.h>
int main(void) {

struct bird {
  int a;
  int b;
};

struct bird const s1 = {
  .a = 9,
};

struct bird const s2 = {
  .b = 7,
};

if (s1 != s2) {
printf("Comparison worked.");}
};
