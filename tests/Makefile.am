noinst_PROGRAMS = test_init

LOG_DRIVER := $(SHELL) tap_wrapper.sh $(top_srcdir)/config/test-driver

TESTS = \
	test_simple.sh \
    test_obj_array.sh \
    test_array_obj.sh \
    test_init

check_PROGRAMS = test_init

EXTRA_DIST = $(TESTS) test_prove.sh tap_wrapper.sh

all :
	if [ "$(abs_srcdir)" != "$(abs_builddir)" ]; then \
	  cp -f $(abs_srcdir)/driver_wrapper.sh .; \
	  cp -f $(abs_srcdir)/tap_wrapper.sh .; \
	  cp -f $(abs_srcdir)/test_*.sh . ; \
	  cp -f $(abs_srcdir)/*.json . ; \
	fi

test :
	prove \
        --formatter TAP::Formatter::JUnit \
        --timer \
        test_prove.sh \
        > junit_result.xml

test_init_SOURCES = test_init.c

test_init_CFLAGS = \
    $(CHECK_CFLAGS) \
    $(SQLITE3_CFLAGS) \
    -I$(top_srcdir)/parser \
    -I$(top_srcdir)/scanner

test_init_LDFLAGS = \
    $(top_builddir)/parser/libparser.la \
    $(top_builddir)/scanner/libscanner.la \
    $(SQLITE3_LIBS) \
    $(CHECK_LIBS)

