ServerFolder=./server/
ClientFolder=./client/
TypesAndUtilsFolder=./types_and_utils/

all: make_server make_utils  make_client

make_utils:
	exho "hey:

make_server:
	make -C $(ServerFolder)

make_client:
	exho "hey:
