// Copyright 2022 Adefe
#include <machine.hpp>

int main(int argc, char **argv) {
  Machine *machine = new Machine;
  machine->ProcessAllBlocks();
  return EXIT_SUCCESS;
}
