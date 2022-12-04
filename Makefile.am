ACLOCAL_AMFLAGS = -I config

SUBDIRS =

EXTRA_DIST = tokenizer.spec

if USE_PARSER
SUBDIRS += tools \
    parser
endif

SUBDIRS += \
	scanner \
	tokenizer \
	tests

test :
	$(MAKE) check

rpm :
	rm -rf $(top_srcdir)/rpmbuild
	mkdir -p $(top_srcdir)/rpmbuild/SOURCES/
	cp -f $(PACKAGE_NAME)-$(PACKAGE_VERSION).tar.gz $(top_srcdir)/rpmbuild/SOURCES/
	rpmbuild --bb $(PACKAGE_NAME).spec \
		--define "_topdir $(abs_top_srcdir)/rpmbuild" \
		--target x86_64-linux-gnu

