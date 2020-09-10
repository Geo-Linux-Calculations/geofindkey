PROJNAME      = geofindkey
PROGNAME1     = geofindkey
PROGNAME2     = geoszbtoyxh
PROGNAME3     = geositer500
PROGNAME4     = geofindkey2p
SRCS          = src
PROGS         = $(PROGNAME1) $(PROGNAME2) $(PROGNAME3) $(PROGNAME4)
CPP           = gcc
CFLAGS        = -Wall -g
LIBS          = -lm
VER           = 2
REL           = 0
PREFIX        = /usr/local
INSTALL       = install
LN            = ln -fs

.PHONY: all clean install

all: $(PROGS)

clean:
	rm -f $(PROGS)

$(PROGNAME1): $(SRCS)/$(PROGNAME1).c
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

$(PROGNAME2): $(SRCS)/$(PROGNAME2).c
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

$(PROGNAME3): $(SRCS)/$(PROGNAME3).c
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

$(PROGNAME4): $(SRCS)/$(PROGNAME4).c
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

install: $(PROGS)
	$(INSTALL) -d $(PREFIX)/bin
	$(INSTALL) -m 0755 $(PROGS) $(PREFIX)/bin/
	$(INSTALL) -d $(PREFIX)/share/man/man1
	$(INSTALL) -m 0644 man/man1/*.1 $(PREFIX)/share/man/man1
	$(INSTALL) -d $(PREFIX)/share/doc/$(PROJNAME)
	$(INSTALL) -m 0644 LICENSE README.md doc/* $(PREFIX)/share/doc/$(PROJNAME)
