#Paths
Binaries=./binaries/
Include=./include/
Libraries=./libraries/
ResultMachine=./result_machine/
ResultServerApp=./result_server_application/
Scripts=./scripts/
SourcesMachine=./sources_machine/
SourcesCommon=./sources_common/
SourcesServerApp=./sources_server_application/
Test=./test/
Deploy=./deploy/
#Names
ServerApp=RattlesnakeServer
Machine=RattlesnakeMachine
#Compilation
Compiler=g++
Flags=-I $(Include) -I ../libs/network/include/ -I ../libs/data_processing/include/ -L $(Libraries) -L /usr/lib/ -L ../libs/build/data_processing/ -L ../libs/build/network/ -Ofast -std=c++2a -Wall -Werror -Wpedantic
TestFlags=-lgtest -lpthread -coverage -lgcov
Archiver=ar

all: clean_dirs check make_binaries make_server_app make_machine make_test_binaries make_test_server make_test_machine run_tests make_report

clean_dirs:
	@echo "-------------START CLEANUP OF $(Result), $(ResultMachine), $(ResultServerApp) AND $(Libraries)-------------"
	rm -f $(Binaries)*
	rm -f $(ResultMachine)*
	rm -f $(ResultServerApp)*
	rm -f $(Libraries)*
	find $(Test) -type f -not -name "appinfo_test.cpp" -not -name "dbhelper_test.cpp" -not -name "machine_factory_test.cpp" -not -name "machine_test.cpp" -not -name "server_application_test.cpp" -not -name "test_machine.cpp" -not -name "test_server.cpp" -delete
	rm -rf $(Test)report*

check:
	@echo "-------------START FORMATTING FILES-------------"
	$(Scripts)prepare.sh
	@echo "-------------START CHECKING FILES-------------"
	$(Scripts)check.sh

make_binaries:	$(SourcesCommon)appinfo.cpp $(SourcesCommon)dbhelper.cpp $(SourcesCommon)machine_factory.cpp
	$(Compiler) $(Flags) -c $(SourcesCommon)appinfo.cpp -o $(Binaries)appinfo.o
	$(Archiver) -crv $(Libraries)libappinfo.a $(Binaries)appinfo.o
	$(Compiler) $(Flags) -c $(SourcesCommon)dbhelper.cpp -o $(Binaries)dbhelper.o
	$(Archiver) -crv $(Libraries)libdbhelper.a $(Binaries)dbhelper.o
	$(Compiler) $(Flags) -c $(SourcesCommon)machine_factory.cpp -o $(Binaries)machine_factory.o
	$(Archiver) -crv $(Libraries)libmachine_factory.a $(Binaries)machine_factory.o

make_server_app: $(Binaries)appinfo.o  $(Binaries)dbhelper.o $(Binaries)machine_factory.o $(Binaries)main_server.o $(Binaries)server_application.o
	$(Compiler) $(Flags)  $(Binaries)main_server.o $(Binaries)server_application.o -o $(ResultServerApp)$(ServerApp) -lappinfo -ldbhelper -lmachine_factory -ldata_processing -lnetwork -lmysqlclient

$(Binaries)main_server.o : $(SourcesServerApp)main_server.cpp
	$(Compiler) $(Flags) -c $(SourcesServerApp)main_server.cpp -o $(Binaries)main_server.o

$(Binaries)server_application.o : $(SourcesServerApp)server_application.cpp
	$(Compiler) $(Flags) -c $(SourcesServerApp)server_application.cpp -o $(Binaries)server_application.o

make_machine: $(Binaries)appinfo.o  $(Binaries)dbhelper.o $(Binaries)main_machine.o $(Binaries)machine.o
	$(Compiler) $(Flags)   $(Binaries)main_machine.o $(Binaries)machine.o -o $(ResultMachine)$(Machine) -lappinfo -ldbhelper -ldata_processing -lnetwork -lmysqlclient

$(Binaries)main_machine.o : $(SourcesMachine)main_machine.cpp
	$(Compiler) $(Flags) -c $(SourcesMachine)main_machine.cpp -o $(Binaries)main_machine.o

$(Binaries)machine.o : $(SourcesMachine)machine.cpp
	$(Compiler) $(Flags) -c $(SourcesMachine)machine.cpp -o $(Binaries)machine.o

make_test_binaries: $(SourcesCommon)appinfo.cpp $(SourcesCommon)dbhelper.cpp $(SourcesCommon)machine_factory.cpp
	$(Compiler) $(Flags) -c $(SourcesCommon)appinfo.cpp -o $(Test)appinfo.o $(TestFlags)
	$(Compiler) $(Flags) -c $(SourcesCommon)dbhelper.cpp -o $(Test)dbhelper.o $(TestFlags)
	$(Compiler) $(Flags) -c $(SourcesCommon)machine_factory.cpp -o $(Test)machine_factory.o $(TestFlags)
	$(Compiler) $(Flags) -c $(Test)appinfo_test.cpp -o $(Test)appinfo_test.o $(TestFlags)
	$(Compiler) $(Flags) -c $(Test)dbhelper_test.cpp -o $(Test)dbhelper_test.o $(TestFlags)
	$(Compiler) $(Flags) -c $(Test)machine_factory_test.cpp -o $(Test)machine_factory_test.o $(TestFlags)
	$(Compiler) $(Flags) -c $(Test)machine_test.cpp -o $(Test)machine_test.o $(TestFlags)
	$(Compiler) $(Flags) -c $(Test)server_application_test.cpp -o $(Test)server_application_test.o $(TestFlags)

make_test_server: $(Test)appinfo.o $(Test)dbhelper.o $(Test)machine_factory.o $(Test)test_server.o $(Test)server_application.o $(Test)dbhelper_test.o $(Test)machine_factory_test.o  $(Test)server_application_test.o
	$(Compiler) $(Flags) $(Test)appinfo.o $(Test)dbhelper.o $(Test)machine_factory.o $(Test)test_server.o $(Test)server_application.o $(Test)appinfo_test.o $(Test)dbhelper_test.o $(Test)machine_factory_test.o $(Test)server_application_test.o  -o $(Test)$(ServerApp)TEST $(TestFlags) -ldata_processing -lnetwork -lmysqlclient

$(Test)test_server.o : $(Test)test_server.cpp
	$(Compiler) $(Flags) -c $(Test)test_server.cpp -o $(Test)test_server.o $(TestFlags)

$(Test)server_application.o : $(SourcesServerApp)server_application.cpp
	$(Compiler) $(Flags) -c $(SourcesServerApp)server_application.cpp -o $(Test)server_application.o $(TestFlags)

make_test_machine: $(Test)appinfo.o $(Test)dbhelper.o $(Test)test_machine.o $(Test)machine.o $(Test)machine_test.o
	$(Compiler) $(Flags) $(Test)appinfo.o $(Test)dbhelper.o $(Test)test_machine.o $(Test)machine.o $(Test)machine_test.o -o $(Test)$(Machine)TEST $(TestFlags) -ldata_processing -lnetwork -lmysqlclient

$(Test)test_machine.o : $(Test)test_machine.cpp
	$(Compiler) $(Flags) -c $(Test)test_machine.cpp -o $(Test)test_machine.o $(TestFlags)

$(Test)machine.o : $(SourcesMachine)machine.cpp
	$(Compiler) $(Flags) -c $(SourcesMachine)machine.cpp -o $(Test)machine.o $(TestFlags)

run_tests:
	valgrind $(Test)$(ServerApp)TEST --leak-check=full || true
	valgrind $(Test)$(Machine)TEST --leak-check=full || true

make_report:
	lcov -t $(Test)$(ServerApp)TEST -o $(Test)coverage_server.info -c -d $(Test)
	genhtml -o $(Test)report_server $(Test)coverage_server.info
	lcov -t $(Test)$(Machine)TEST -o $(Test)coverage_machine.info -c -d $(Test)
	genhtml -o $(Test)report_machine $(Test)coverage_machine.info

deploy: make_server_app make_machine
	cp $(ResultMachine)$(Machine) ${Deploy}server/$(Machine)
	cp $(ResultServerApp)$(ServerApp) ${Deploy}server/$(ServerApp)
	sudo docker-compose -f ${Deploy}docker-compose.yml up --force-recreate
