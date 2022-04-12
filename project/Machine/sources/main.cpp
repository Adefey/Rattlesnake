// Copyright 2022 Adefe

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
  if (argc != 3) {
    printf("%s\n", "Usage: ./Executable string file_name");
    return EXIT_FAILURE;
  }
  char *str = argv[1];
  char *file_name = argv[2];
  size_t result = count_letters_in_file(str, file_name);
  printf("%zu\n", result);
  return EXIT_SUCCESS;
}
