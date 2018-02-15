.PHONY: all clean

all: CI_Test.elf

clean:
	rm -vf *.o *.elf

%.o: %.c
	$(CC) -Wall -Wextra -pedantic -c -o $@ $<

CI_Test.elf: CI_Test.o foo.o
	$(CC) -o $@ $^
