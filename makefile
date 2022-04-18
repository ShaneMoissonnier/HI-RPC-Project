include makefile.rules

all: build

build: server client test

server: server.o
	$(BUILD) -o server server.o -lm

client: client.o serialization.o
	$(BUILD) -o client client.o serialization.o

test: test.o
	$(BUILD) -o test test.o serialization.o

clean:
	rm -f *.o server client test
