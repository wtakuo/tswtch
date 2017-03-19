# tswtch : A simple user-level task switching library
# Copyright (c) 2014-2017 Takuo Watanabe

ARCH = $(shell uname -m)
OS = $(shell uname -s)

NAME = tswtch
SRCS = tcontext.c
ASMS = tswtch.S
OBJS = $(SRCS:%.c=%.o) $(ASMS:%.S=%.o)
LIB = lib$(NAME).$(DYLIB_SUFFIX)

CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -O2 -g
CPPFLAGS =
IFLAGS = -I . -I $(ARCH)
LDFLAGS = $(DYLIB_FLAGS)

ifeq ($(ARCH), i386)
CFLAGS += -m32 -mstackrealign
endif

ifeq ($(OS), Darwin)
CFLAGS += -DTSWTCH=_tswtch
DYLIB_FLAGS = -dynamiclib
DYLIB_SUFFIX = dylib
endif
ifeq ($(OS), Linux)
CFLAGS += -fPIC
DYLIB_FLAGS = -shared
DYLIB_SUFFIX = so
endif

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(IFLAGS) -c -o $@ $<

%.o: $(ARCH)/%.S
	$(CC) $(CFLAGS) $(CPPFLAGS) $(IFLAGS) -c -o $@ $<


.PHONY: all clean allclean

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(LIB)
	$(RM) $(OBJS)

allclean: clean
	$(RM) *.o
	$(RM) a.out
	$(RM) *~
	$(RM) .DS_Store

