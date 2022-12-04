LOG_DRIVER := $(SHELL) driver_wrapper.sh $(top_srcdir)/config/test-driver

TESTS = \
	test_simple.sh \
    test_obj_array.sh \
    test_array_obj.sh

EXTRA_DIST = $(TESTS) driver_wrapper.sh tap_wrapper.sh

all :
	if [ "$(abs_srcdir)" != "$(abs_builddir)" ]; then \
	  cp -f $(abs_srcdir)/driver_wrapper.sh .; \
	  cp -f $(abs_srcdir)/tap_wrapper.sh .; \
	  cp -f $(abs_srcdir)/test_*.sh . ; \
	  cp -f $(abs_srcdir)/*.json . ; \
	fi

prove :
	prove \
        --formatter TAP::Formatter::JUnit \
        --timer tap_wrapper.sh \
        > junit_result.xml

test : check

