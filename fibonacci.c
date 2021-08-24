#include <stdlib.h>
size_t fib(size_t n) {      
    if (n < 3)
        return 1;
    else
        return fib(n-1) + fib(n-2);
}

int main(int argc, char* argv[argc+1]) {
    fib(atoi(argv[1]));
}
