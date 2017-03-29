all : 
	mkdir -p bin
	mkdir -p build
	
	make tests
	make sender
	make receiver

tests : build/sendersockets.o build/sender.o build/receiver.o build/receiversockets.o build/fileutils.o build/protocolutils.o build/tester.o build/testmain.o
	gcc -I include $^ -o bin/tester

sender : build/sendersockets.o build/sender.o build/fileutils.o build/protocolutils.o build/sendermain.o
	gcc -I include $^ -o bin/sender

receiver : build/receiver.o build/receiversockets.o build/protocolutils.o build/receivermain.o build/fileutils.o
	gcc -I include $^ -o bin/receiver

build/sendersockets.o : src/sender/sendersockets.c
	gcc -I include $< -c -o $@
build/sender.o : src/sender/sender.c
	gcc -I include $< -c -o $@
build/receiver.o : src/receiver/receiver.c
	gcc -I include $< -c -o $@
build/receiversockets.o : src/receiver/receiversockets.c
	gcc -I include $< -c -o $@
build/fileutils.o : src/utils/fileutils.c
	gcc -I include $< -c -o $@
build/protocolutils.o : src/utils/protocolutils.c
	gcc -I include $< -c -o $@
build/tester.o : src/tester.c
	gcc -I include $< -c -o $@

build/receivermain.o : src/exec/receivermain.c
	gcc -I include $< -c -o $@
build/sendermain.o : src/exec/sendermain.c
	gcc -I include $< -c -o $@
build/testmain.o : src/exec/testmain.c
	gcc -I include $< -c -o $@


clean : 
	rm -rf bin
	rm -rf build
	rm -rf files/*.tar.gz
	rm -rf files/*parts
	rm -rf files/received/*
	
