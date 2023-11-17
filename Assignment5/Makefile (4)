CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic -gdwarf-4 $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)

all:  mathlib-test

mathlib-test: mathlib-test.o euler.o bbp.o e.o madhava.o viete.o newton.o
	$(CC) -lm -o $@ $^ $(LFLAGS)

bbp: bbp.o
	$(CC) -o $@ $^ $(LFLAGS)

e: e.o
	$(CC) -o $@ $^ $(LFLAGS)

madhava: madhava.o
	$(CC) -o $@ $^ $(LFLAGS)

viete: viete.o
	$(CC) -o $@ $^ $(LFLAGS)

newton: newton.o
	$(CC) -o $@ $^ $(LFLAGS)


%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f euler e bbp madhava newton mathlib-test viete *.o

format:
	clang-format -i -style=file *.[ch]

