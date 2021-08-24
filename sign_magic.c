/* Simple pre-processor test to abort compilation if the representation is not
   in 2's complement. Uses the bit-trick from page 61 of modern C.*/

#if ((-1 & 3) - 3 != 0)
# error "Not two's complement"
# endif

void main (void) {}
