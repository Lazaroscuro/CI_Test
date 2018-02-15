.PHONY: all clean test

all: CI_Test.elf

clean:
	rm -vf *.o *.elf *.xml

test: testsuite.elf
	./testsuite.elf

%.o: %.c
	$(CC) -Wall -Wextra -pedantic -c -o $@ $<

%.o: %.cpp
	$(CXX) -Wall -Wextra -pedantic -c -o $@ $<

CI_Test.elf: CI_Test.o foo.o
	$(CC) -o $@ $^

testsuite.elf: test_foo.o foo.o
	$(CXX) -o $@ $^ -lcppunit
