include makefile.rules

all: build

build: server client

server: server.o
	$(BUILD) -o server server.o -lm

client: client.o
	$(BUILD) -o client client.o

clean:
	rm -f *.o server client
