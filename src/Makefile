# tswtch : A simple user-level task switching library
# Copyright (c) 2014-2017 Takuo Watanabe

ARCH = $(shell uname -m)
OS = $(shell uname -s)

NAME = tswtch
SRCS = tcontext.c
HDRS = tcontext.h $(ARCH)/tcontextstr.h
ASMS = tswtch.S
OBJS = $(SRCS:%.c=%.o) $(ASMS:%.S=%.o)
LIB = lib$(NAME).$(DYLIB_SUFFIX)

CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -O2 -g
CPPFLAGS =
IFLAGS = -I . -I $(ARCH)
LDFLAGS = $(DYLIB_FLAGS)

RM = rm -f
MKDIR = mkdir
CP = cp

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

PREFIX = /opt
INCDIR = $(PREFIX)/include/$(NAME)
LIBDIR = $(PREFIX)/lib

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(IFLAGS) -c -o $@ $<

%.o: $(ARCH)/%.S
	$(CC) $(CFLAGS) $(CPPFLAGS) $(IFLAGS) -c -o $@ $<


.PHONY: all clean allclean

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

tcontext.o: tcontext.h $(ARCH)/tcontextstr.h

install: $(LIB)
	$(MKDIR) -p $(INCDIR)
	$(CP) $(HDRS) $(INCDIR)
	$(MKDIR) -p $(LIBDIR)
	$(CP) $(LIB) $(LIBDIR)

clean:
	$(RM) $(LIB)
	$(RM) $(OBJS)

allclean: clean
	$(RM) *.o
	$(RM) a.out
	$(RM) *~
	$(RM) .DS_Store
