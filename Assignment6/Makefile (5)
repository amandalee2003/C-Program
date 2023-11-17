CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic -gdwarf-4 $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)

all:  sorting

sorting: sorting.o stats.o set.o batcher.o heap.o quick.o shell.o
	$(CC) -o $@ $^ $(LFLAGS)

batcher: stats.o set.o batcher.o
	$(CC) -o $@ $^ $(LFLAGS)

heap: stats.o heap.o
	$(CC) -o $@ $^ $(LFLAGS)

shell: stats.o shell.o
	$(CC) -o $@ $^ $(LFLAGS)

quick: stats.o quick.o
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f sorting shell batcher set heap quick stats *.o

format:
	clang-format -i -style=file *.[ch]
