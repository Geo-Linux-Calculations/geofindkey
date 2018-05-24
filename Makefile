PROGNAME1     = geofindkey
PROGNAME2     = geoszbtoyxh
PROGS         = $(PROGNAME1) $(PROGNAME2)
CPP           = gcc
CFLAGS        = -Wall -s
LIBS          = -lm
VER           = 1
REL           = 5
PREFIX        = /usr/local
INCPREFIX     = $(PREFIX)/include
LIBPREFIX     = $(PREFIX)/lib
MANPREFIX     = $(PREFIX)/share/man/man1
INSTALL       = install
LN            = ln -fs

.PHONY: all clean install

all: $(PROGS)

clean:
	rm -f $(PROGS)

$(PROGNAME1): $(PROGNAME1).c
	$(CPP) $(CFLAGS) $(LIBS) $^ -o $@

$(PROGNAME2): $(PROGNAME2).c
	$(CPP) $(CFLAGS) $(LIBS) $^ -o $@

install: $(PROGNAME)
	$(INSTALL) -d $(PREFIX)/bin
	$(INSTALL) -m 0755 $(PROGNAME1) $(PREFIX)/bin/
	$(INSTALL) -m 0755 $(PROGNAME2) $(PREFIX)/bin/
