#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <tgmath.h>

// Convert a string to a decimal, and return a pointer for the next
// element of the string.
// NOTE: Bounds checking not yet implemented; will fail on large strings.
// NOTE: Does not work with scientific notation yet
double my_strtod(char* const s, char **endptr){
  // Scrolling index variable
  signed i = 0;
  // Index variable for the decimal point 
  signed p = -1;
  
  // Check if negative
  signed sign = 1;
  if (s[0] == '-') {
    sign = -1;
    ++i;
  }


  // initialize result
  double result = 0;

  // Read the input
  while (s[i] != 0){
    if ('0' <= s[i]  && s[i] <= '9'){
      result = result * 10 + (s[i] - '0');
    } else if (s[i] == '.'){
      p = i + 1; // accounts for the "digit" of the decimal place
    } else {
      *endptr = &s[i];
      break;
    }
    ++i;
  }
  
  // If p wasn't changed, then no decimal point was read. 
  if (p == -1) {
    p = i;
  }

  
  // Adjust result according to decimal point and sign
  result = sign * result * pow(10, p - i);
  return result;
}

int main(int argc, char* const argv[argc+1]){
  char *ptr = NULL;
  printf("You entered: %f\n", my_strtod(argv[1], &ptr));
  if (ptr != NULL){
    printf("String part is: %s\n", ptr);
  }
}

  
