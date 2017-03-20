# tswtch : A simple user-level task switching library
# Copyright (c) 2014-2017 Takuo Watanabe

SRCDIR = src
TESTSDIR = tests

RM = rm -f

.PHONY: all lib tests clean allclean

all: lib tests

lib:
	$(MAKE) -C $(SRCDIR)

install:
	$(MAKE) -C $(SRCDIR) install

tests:
	$(MAKE) -C $(TESTSDIR) INCDIR=../$(SRCDIR) LIBDIR=../$(SRCDIR)

run%: $(TESTSDIR)/test%
	$(MAKE) -C $(TESTSDIR) LIBDIR=../$(SRCDIR) $@

clean:
	$(MAKE) -C $(SRCDIR) clean
	$(MAKE) -C $(TESTSDIR) clean

allclean:
	$(MAKE) -C $(SRCDIR) allclean
	$(MAKE) -C $(TESTSDIR) allclean
	$(RM) *~
	$(RM) .DS_Store
