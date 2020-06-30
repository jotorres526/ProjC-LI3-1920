CC = gcc
CFLAGS = -g -Wall -ansi -O3

src = $(wildcard src/*.c) \
      $(wildcard libs/*.c)
obj = $(src:.c=.o)

program: $(obj)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm $(obj) program
