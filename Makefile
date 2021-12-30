PROJNAME      = geofindkey
PROGNAME1     = geofindkey
PROGNAME2     = geoszbtoyxh
PROGNAME3     = geositer500
PROGNAME4     = geoconformal
PROGNAME5     = geodeform500
PROGNAME6     = geohelmert3d
SRCS          = src
PROGS         = $(PROGNAME1) $(PROGNAME2) $(PROGNAME3) $(PROGNAME4) $(PROGNAME5) $(PROGNAME6)
CC            = gcc
CFLAGS        = -Wall -s
LIBS          = -lm
VER           = 2
REL           = 2
PREFIX        = /usr/local
INSTALL       = install
LN            = ln -fs
GROFF2PDF     = groff -m man -T pdf
RM            = rm -f

.PHONY: all clean install

all: $(PROGS)

clean:
	$(RM) $(PROGS) man_*.pdf

$(PROGNAME1): $(SRCS)/$(PROGNAME1).c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(PROGNAME2): $(SRCS)/$(PROGNAME2).c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(PROGNAME3): $(SRCS)/$(PROGNAME3).c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(PROGNAME4): $(SRCS)/$(PROGNAME4).c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(PROGNAME5): $(SRCS)/$(PROGNAME5).c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(PROGNAME6): $(SRCS)/$(PROGNAME6).c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

manual: man_$(PROGNAME1).pdf man_$(PROGNAME2).pdf man_$(PROGNAME3).pdf man_$(PROGNAME4).pdf man_$(PROGNAME5).pdf man_$(PROGNAME6).pdf

man_$(PROGNAME1).pdf: man/man1/$(PROGNAME1).1
	$(GROFF2PDF) $^ > $@

man_$(PROGNAME2).pdf: man/man1/$(PROGNAME2).1
	$(GROFF2PDF) $^ > $@

man_$(PROGNAME3).pdf: man/man1/$(PROGNAME3).1
	$(GROFF2PDF) $^ > $@

man_$(PROGNAME4).pdf: man/man1/$(PROGNAME4).1
	$(GROFF2PDF) $^ > $@

man_$(PROGNAME5).pdf: man/man1/$(PROGNAME5).1
	$(GROFF2PDF) $^ > $@

man_$(PROGNAME6).pdf: man/man1/$(PROGNAME6).1
	$(GROFF2PDF) $^ > $@

install: $(PROGS)
	$(INSTALL) -d $(PREFIX)/bin
	$(INSTALL) -m 0755 $(PROGS) $(PREFIX)/bin/
	$(INSTALL) -d $(PREFIX)/share/man/man1
	$(INSTALL) -m 0644 man/man1/*.1 $(PREFIX)/share/man/man1
	$(INSTALL) -d $(PREFIX)/share/doc/$(PROJNAME)
	$(INSTALL) -m 0644 LICENSE README.md doc/* $(PREFIX)/share/doc/$(PROJNAME)
