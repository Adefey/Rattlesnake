// Copyright 2022 Adefe
#include <machine.hpp>

int main(int argc, const char **argv) {
  if (argc != 3) {
    return EXIT_FAILURE;
  }
  std::string scheme = argv[1];
  std::string vars = argv[2];
  Machine *machine = new Machine(scheme, vars);
  machine->ProcessAllBlocks();
  return EXIT_SUCCESS;
}
