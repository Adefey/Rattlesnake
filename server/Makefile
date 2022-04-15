#Paths
Binaries=./binaries/
Include=./include/
Libraries=./libraries/
ResultMachine=./result_machine/
ResultServerApp=./result_server_application/
Scripts=./scripts/
SourcesMachine=./sources_machine/
SourcesServerApp=./sources_server_app/
Test=./test/
#Names
ServerApp=RattlesnakeServer
Machine=RattlesnakeMachine
#Compilation
Compiler=g++
Flags=-I $(Headers) -Ofast -std=c++2a -Wall -Werror -Wpedantic
Archiver=ar

all: clean_dirs check

clean_dirs:
	@echo "-------------START CLEANUP OF $(Result), $(ResultMachine), $(ResultServerApp) AND $(Libraries)-------------"
	rm -f $(Binaries)*
	rm -f $(ResultMachine)*
	rm -f $(ResultServerApp)*
	rm -f $(Libraries)*

check:
	@echo "-------------START FORMATTING FILES-------------"
	$(Scripts)prepare.sh
	@echo "-------------START CHECKING FILES-------------"
	$(Scripts)check.sh

