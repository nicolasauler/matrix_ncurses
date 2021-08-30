CFLAGS=-Wall -Wextra -Wshadow -Wconversion -Wcast-align -Wunused -Wmissing-prototypes -Wno-missing-braces -ansi -pedantic -g -O2 -D_POSIX_C_SOURCE=199309L
CC=gcc
OBJS=main.o matrix.o ui.o

all: main
	
main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o main
