LOG_DRIVER := $(SHELL) driver_wrapper.sh $(top_srcdir)/config/test-driver

#TEST_EXTENSIONS = .sh
#SH_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
#	my-test-driver

TESTS = \
	test_simple.sh \
    test_obj_array.sh \
    test_array_obj.sh

EXTRA_DIST = $(TESTS) my-test-driver

all :
	if [ "$(abs_srcdir)" != "$(abs_builddir)" ]; then \
	  cp -f $(abs_srcdir)/my-test-driver .; \
	  cp -f $(abs_srcdir)/*.sh . ; \
	  cp -f $(abs_srcdir)/*.json . ; \
	fi

prove :
	prove --formatter TAP::Formatter::JUnit test_*.t > junit_results.xml

prove2 :
	prove --formatter TAP::Formatter::JUnit tap_wrapper.sh

test : check

