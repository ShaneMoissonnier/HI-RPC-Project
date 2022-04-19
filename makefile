include makefile.rules

all: build

build: server client test_unit

server: server.o
	$(BUILD) -o server server.o -lm

client: client.o serialization.o
	$(BUILD) -o client client.o serialization.o

test: $(TESTS)
	for file in $(TESTS);do ./$$file;done

CuTest.o: cutest/CuTest.c cutest/CuTest.h
	$(CC) -c $< $(CFLAGS)

AllTests.o: cutest/AllTests.c cutest/AllTests.h cutest/CuTest.h serialization.h
	$(CC) -c $< $(CFLAGS)

test_unit: AllTests.o CuTest.o serialization.o
	$(CC) -o $@ $^ $(CFLAGS)


clean:
	rm -f *.o server client test_unit
