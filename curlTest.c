#include <stdio.h>
#include <stdlib.h>

#include "curl_utils.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s url\n", argv[0]);
    exit(1);
  }
  char *result = getContent(argv[1]);
  printf("result = \n%s\n", result);
  return 0;
}
