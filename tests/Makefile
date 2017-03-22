# tswtch : A simple user-level task switching library
# Copyright (c) 2014-2017 Takuo Watanabe

ARCH = $(shell uname -m)
OS = $(shell uname -s)

NAME = tswtch
SRCS = $(EXES:%=%.c)
OBJS = $(SRCS:%.c=%.o)
EXES = test0 test1 test2 test3

CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -O2 -g
CPPFLAGS =
IFLAGS = -I $(INCDIR) -I $(INCDIR)/$(ARCH)
LDFLAGS = 
LIBS = -L $(LIBDIR) -l$(NAME)

#PREFIX = /opt
#INCDIR = $(PREFIX)/include/$(NAME)
#LIBDIR = $(PREFIX)/lib
INCDIR = ../src
LIBDIR = ../src

ifeq ($(ARCH), i386)
CFLAGS += -m32 -mstackrealign
endif
ifeq ($(OS), Darwin)
LD_PATH_VAR = DYLD_LIBRARY_PATH
endif
ifeq ($(OS), Linux)
CFLAGS += -fPIC
LD_PATH_VAR = LD_LIBRARY_PATH
endif

.PHONY: all clean allclean

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(IFLAGS) -c -o $@ $<

test%: test%.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

run%: test%
	$(LD_PATH_VAR)=$(LIBDIR) ./$<

all: $(EXES)

clean:
	$(RM) $(EXES)
	$(RM) $(OBJS)
	$(RM) -r *.dSYM

allclean: clean
	$(RM) *.o
	$(RM) a.out
	$(RM) *~
	$(RM) .DS_Store
