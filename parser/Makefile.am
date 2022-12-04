lib_LTLIBRARIES = libparser.la

LEMON = $(abs_top_builddir)/tools/lemon
MAKEHEADERS = $(abs_top_builddir)/tools/makeheaders

LEMPAR = $(abs_top_srcdir)/tools/lempar.c

BUILT_SOURCES = $(top_srcdir)/parser/parser.c $(top_srcdir)/parser/parser.h

CLEANFILES = $(top_srcdir)/parser/parser.c $(top_srcdir)/parser/parser.h

libparser_la_SOURCES = $(top_srcdir)/parser/parser.c userdata.c str.c

libparser_la_CFLAGS  = -I$(top_srcdir)/parser

$(top_srcdir)/parser/parser.h : $(top_srcdir)/parser/parser.c token.h
	{ \
	echo '#ifndef PARSER_H'; \
	echo ''; \
	echo '#define PARSER_H'; \
	echo '#include "token.h"'; \
	echo '#include "userdata.h"'; \
	$(MAKEHEADERS) -h $<; \
	echo ''; \
	echo '#endif /* #define PARSER_H */'; \
	} > $@

$(top_srcdir)/parser/parser.c : $(top_srcdir)/parser/parser.y
	cd $(top_srcdir)/parser && \
	$(LEMON) T=$(LEMPAR) -s -m parser.y && \
    { if test $$? -ne 0; then rm -f parser.c ; exit 1; fi }

