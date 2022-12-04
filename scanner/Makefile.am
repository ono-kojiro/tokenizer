lib_LTLIBRARIES = libscanner.la

EXTRA_DIST = scanner.re

BUILT_SOURCES = scanner.c

libscanner_la_SOURCES = \
    scanner.c \
    scanner.h \
    input.c \
    input.h

libscanner_la_CFLAGS = \
	-I$(top_srcdir)/parser

-include scanner.dep

.re.c :
	$(RE2C) -o $@ --depfile scanner.dep $<

