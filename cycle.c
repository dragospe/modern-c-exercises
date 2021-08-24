#include <stdio.h>
#include <stdlib.h>

void three_cycle_double(double* p0, double* p1, double* p2){
  double tmp = *p0;
  *p0 = *p2;
  *p2 = *p1;
  *p1 = tmp;
}


int main(int argc, char* argv[argc+1]){
  if (argc != 4) {
    printf("Must pass three arguments\n");
    return 1;
      };
  double x = strtod(argv[1],0);
  double y = strtod(argv[2],0);
  double z = strtod(argv[3],0);

  double* p0 = &x;
  double* p1 = &y;
  double* p2 = &z;
    
  printf("Inputs were: %g, %g, %g\n", *p0, *p1, *p2);
  three_cycle_double(p0, p1, p2);
  
  printf("Outputs are: %g, %g, %g\n", *p0, *p1, *p2);
  return 0;
};
