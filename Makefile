ServerFolder=./server/
ClientFolder=./UI/
LibsFolder=./libs/

all: make_utils make_server make_client

make_utils:
	cd $(LibsFolder) && rm -rf build/ && mkdir build && cd build/ && cmake .. && cmake --build . && valgrind ./data_processing/data_processing_test && valgrind ./network/network_test && cd ../..

make_server:
	make -C $(ServerFolder)

make_client:
	cd $(ClientFolder) && rm -rf build/ && mkdir build && cd build/ && cmake .. && cmake --build . && valgrind ./UITest && cd ../..
