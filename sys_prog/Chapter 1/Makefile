CC     = gcc
CFLAGS = -Wall -Wextra -O2

%.out: %.c
	$(CC) $(CFLAGS) -o $@ $<

OUTS = $(patsubst %.c,%.out,$(wildcard *.c))

all: $(OUTS)

clean:
	rm -f *.out
