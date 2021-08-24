# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <stdbool.h>
# include <string.h>

enum {buf_max = 32,};

size_t line_number = 0;

int cat_via_buffer(char buffer[], size_t buf_max,
		   FILE * instream, FILE * outstream, bool numbered) {
  while (fgets(buffer, buf_max, instream)) {
    if (numbered) {
      fprintf(outstream, "%lu ", line_number++);
    }
    fputs(buffer, outstream);
  }
    fclose(instream);
    return EXIT_SUCCESS;
}


int main ( int argc, char* argv[argc+1]) {
  int ret = EXIT_FAILURE;
  char buffer[buf_max] = { 0 };
  int arg_idx = 1;
  
  bool numbered = false;
  // Check if the first argument is "-n"
  if (argc > 1 && !strcmp(argv[1], "-n")){
    numbered = true;
    arg_idx = 2;
  }

  // Read from stdin if no arguments passed
  if (argc == 1 || (argc == 2 && numbered == true)){
    ret = cat_via_buffer(buffer, buf_max, stdin, stdout, numbered);
  }
  
  for (; arg_idx < argc; ++arg_idx) {
    // Processes args
    FILE * instream = fopen(argv[arg_idx], "r"); // as filenames
    if (instream) {
      ret = cat_via_buffer(buffer, buf_max, instream, stdout, numbered);
    } else {
      /* Provides some error diagnostic . */
      fprintf(stderr, "Could not open %s: ", argv[arg_idx]);
      perror(0);
      errno = 0;
      // Resets the error code
    }
  }
  return ret ;
}
