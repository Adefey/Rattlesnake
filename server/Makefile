#Paths
ProjectPath=./project/
ServerPath=./project/server
ServerAppSources=./project/server/sources_server_application/
MachineSources=./project/server/sources_machine/
ServerHeaders=/headers/
Binaries=/binaries/
Libraries=/libraries/
Result=/result/
Tests=/test/
CommonScripts=./scripts/
#Names
Server=RattlesnakeServer
Machine=RattlesnakeMachine
#Compilation
Compiler=g++
Flags=-I $(Headers) -Ofast -std=c++2a -Wall -Werror -Wpedantic
Archiver=ar
#Testing
TestFolder=./tests/results/

all: clean_dirs check

clean_dirs:
	@echo "-------------START CLEANUP OF $(Result) AND $(Libraries)-------------"
	rm -f $(Binaries)*
	rm -f $(Result)*
	rm -f $(Libraries)*
	find $(Tests) -type f -not -name "main_single.cpp" -not -name "main_multi.cpp" -not -name "test.txt" -delete

check:
	@echo "-------------START FORMATTING FILES-------------"
	$(Scripts)prepare.sh
	@echo "-------------START CHECKING FILES-------------"
	$(Scripts)check.sh

