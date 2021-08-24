#include <inttypes.h>
#include <stdio.h>

typedef union unsignedInspect unsignedInspect;
union unsignedInspect {
  unsigned val;
  unsigned char bytes[sizeof(unsigned)];
};

unsignedInspect twofold = {.val = 0xAABBCCDD,};

void main(void){
printf("value is 0x%.08X\n", twofold.val);
for (size_t i = 0; i < sizeof twofold.bytes; ++i)
  printf("byte[%zu]: 0x%0.2hhX\n", i, twofold.bytes[i]);
};
