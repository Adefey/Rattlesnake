ServerFolder=./server/
ClientFolder=./UI/
LibsFolder=./libs/

all: make_utils make_server make_client

make_utils:
	cd $(LibsFolder) && rm -rf build/ && mkdir build && cd build/ && pwd && cmake .. && cmake --build . && ./data_processing/data_processing_test && ./network/network_test && cd ../..

make_server:
	make -C $(ServerFolder)

make_client:
	cd $(ClientFolder) && rm -rf build/ && mkdir build && cd build/ && pwd && cmake .. && cmake --build . && ./UITest && cd ../..
