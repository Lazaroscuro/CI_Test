.PHONY: all clean test

all: CI_Test.elf

clean:
	rm -vf *.o *.elf *.xml

test: testsuite.elf
	./testsuite.elf

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

CI_Test.elf: CI_Test.o foo.o
	$(CC) -o $@ $^

testsuite.elf: test_foo.o foo.o
	$(CXX) -o $@ $^ -lcppunit

CFLAGS=-Wall -Wextra -pedantic 
CXXFLAGS=-std=c++11 $(CFLAGS)
