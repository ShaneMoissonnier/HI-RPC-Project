include makefile.rules

all: build
	./generator specification.proto
	make instance

build: generator test_unit

server: server.o
	$(BUILD) -o server server.o -lm

client: client.o serialization.o parser.o
	$(BUILD) -o client client.o serialization.o parser.o

instance:
	make client
	make server

test: $(TESTS)
	for file in $(TESTS);do ./$$file;done

generator: generator.o parser.o
	$(BUILD) -o generator generator.o parser.o

CuTest.o: cutest/CuTest.c cutest/CuTest.h
	$(BUILD) -c $<

AllTests.o: cutest/AllTests.c cutest/AllTests.h cutest/CuTest.h serialization.h
	$(BUILD) -c $< 

test_unit: AllTests.o CuTest.o serialization.o
	$(BUILD) -o $@ $^ 

clean:
	rm -f *.o server client generator test_unit replace.txt
	make clean-generate

clean-generate:
	rm -f client_stub.h server_stub.h
