include ../Makefile.inc

CC      ?= gcc
CFLAGS  += -D_XOPEN_SOURCE=700 -D_DEFAULT_SOURCE -Wall -Wextra -g
CPPFLAGS+= -I$(SPL_INCLUDE_DIR)
LDFLAGS += -L$(SPL_LIB_DIR)
LDLIBS  += -lspl -lm -lrt

SRCS := $(wildcard *.c)
OUTS := $(SRCS:.c=.out)
OBJS := $(SRCS:.c=.o)

.PHONY: all clean
all: $(OUTS)

# Compile .c -> .o (make has a builtin rule, but we make dependencies explicit)
%.o: %.c $(SPL_HDRS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

# Link .o -> .out, ensuring the library is present
%.out: %.o $(SPL_LIB)
	$(CC) $(LDFLAGS) -o $@ $< $(LDLIBS)

clean:
	-rm -f $(OUTS) $(OBJS)
