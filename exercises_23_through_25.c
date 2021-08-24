#include <stdio.h>
#include <stddef.h>

typedef union pointerbytes pointerbytes;
union pointerbytes {
  double* ptr;
  unsigned char bytes[sizeof(double*)];
};
double d = 3.14;
pointerbytes p = {.ptr = &d};


double a[] = {1.0, 2.0};
pointerbytes ptr_a = {.ptr = &a};

void main(void){
  printf("The original pointer is: %p\n", p);
  for (size_t i = 0; i < sizeof p.bytes; ++i){
    printf("byte[%zu]: 0x%.02hhx\n",i, p.bytes[i]);
  }

  printf("As pointer: a = %p\n", a);
  printf("As pointer: &a[0] = %p\n", &a[0]);
  printf("As pointer: &a[1] = %p\n", &a[1]);
};
