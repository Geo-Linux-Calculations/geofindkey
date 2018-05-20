PROGNAME      = geofindkey
CPP           = gcc
CFLAGS        = -Wall -s
LIBS          = -lm
VER           = 1
REL           = 2
PREFIX        = /usr/local
INCPREFIX     = $(PREFIX)/include
LIBPREFIX     = $(PREFIX)/lib
MANPREFIX     = $(PREFIX)/share/man/man1
INSTALL       = install
LN            = ln -fs

.PHONY: all clean install

all: $(PROGNAME)

clean:
	rm -f $(PROGNAME)

$(PROGNAME): $(PROGNAME).c
	$(CPP) $(CFLAGS) $(LIBS) $^ -o $@


install: $(PROGNAME)
	$(INSTALL) -d $(PREFIX)/bin
	$(INSTALL) -m 0755 $(PROGNAME) $(PREFIX)/bin/
