ACLOCAL_AMFLAGS = -I config
	
SUBDIRS = \
	scanner \
	example \
	tests

if USE_PARSER
SUBDIRS += parser
endif

test :
	$(MAKE) check

