bin_PROGRAMS = tokenizer

tokenizer_SOURCES = tokenizer.c

tokenizer_CFLAGS = \
	-I$(top_srcdir)/scanner

if USE_PARSER
tokenizer_CFLAGS += \
	-I$(top_srcdir)/parser
endif

tokenizer_LDFLAGS = \
	$(SQLITE3_CFLAGS)

tokenizer_LDADD = \
	$(top_builddir)/scanner/libscanner.la


if USE_PARSER
tokenizer_LDADD += \
	$(top_builddir)/parser/libparser.la
endif

tokenizer_LDADD += \
	$(SQLITE3_LIBS)


