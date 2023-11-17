CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic -gdwarf-4 $(shell pkg-config --cflags gmp)
#LFLAGS = $(shell pkg-config --libs gmp)
LDFLAGS = -g -lncurses

all:  life

test: test.o universe.o
	$(CC) -o $@ $^ $(LDFLAGS)

life: life.o universe.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f universe test life *.o

format:
	clang-format -i -style=file *.[ch]

