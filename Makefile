PROTOCOLDIR = src/protocol
SENDERDIR = src/sender
RECEIVERDIR = src/receiver

NO_MAIN = $(shell find | grep [.]c | grep -v receiver[.]c | grep -v sender[.]c)

all:
	make sender
	make receiver

sender : $(SENDERDIR)/*.c $(PROTOCOLDIR)/*.c 
	mkdir -p bin
	gcc $^ -I include -o bin/sender.out

receiver : $(RECEIVERDIR)/*.c $(PROTOCOLDIR)/*.c 
	mkdir -p bin
	gcc $^ -I include -o bin/receiver.out

tests : $(NO_MAIN)
	mkdir -p bin
	gcc $^ -I include -o bin/test.out

clean : 
	rm -rf bin
