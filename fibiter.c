#include <stdlib.h>
#include <stdio.h>

// Memoized fibonnaci algorithm; remember past results.
void fib2iter(size_t n, size_t buf[2]) {
  for (int i = 2; i < n; ++i){
    size_t res = buf[0] + buf[1];
    buf[1] = buf[0];
    buf[0] = res;
  }
}

size_t fib2(size_t n) {
  size_t res[2] = {1, 1,};
  fib2iter(n, res);
  return res[0];
}

int main(int argc, char* argv[argc+1]) {
    int r = fib2(atoi(argv[1]));
    printf("Result is: %d\n", r);
}
