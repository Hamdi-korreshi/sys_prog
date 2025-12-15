include ../Makefile.inc

CC     ?= gcc
AR     ?= ar
RANLIB ?= ranlib

# All support-library source files live here
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

CFLAGS   += -D_XOPEN_SOURCE=700 -D_DEFAULT_SOURCE -Wall -Wextra -g
CPPFLAGS += -I../include

.PHONY: all clean

all: $(SPL_LIB)

# Build ../lib/libspl.a from common/*.o
$(SPL_LIB): $(OBJS) | $(SPL_LIB_DIR)
	$(AR) rcs $@ $(OBJS)
	$(RANLIB) $@

# Ensure ../lib exists
$(SPL_LIB_DIR):
	mkdir -p $(SPL_LIB_DIR)

%.o: %.c ../include/%.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f $(OBJS) $(SPL_LIB)
