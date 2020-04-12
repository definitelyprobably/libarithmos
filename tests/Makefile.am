#AM_CXXFLAGS = $(OPTIM_CXXFLAGS) $(HARDEN_CXXFLAGS)

check_PROGRAMS = usage
usage_CPPFLAGS = -I$(top_srcdir)/src $(HARDEN_CPPFLAGS)
usage_CXXFLAGS = $(OPTIM_CXXFLAGS) $(HARDEN_CXXFLAGS)
usage_LDFLAGS = $(HARDEN_LDFLAGS)
usage_LDADD = $(top_builddir)/src/libarithmos.la
usage_SOURCES = usage.cpp


libarithmos_installcheck_built_file = .libarithmos_installcheck_built


$(srcdir)/package.m4: $(top_srcdir)/configure.ac
	:;{ \
		echo '# Signature of the current package.' && \
		echo 'm4_define([AT_PACKAGE_NAME],' && \
		echo '  [$(PACKAGE_NAME)])' && \
		echo 'm4_define([AT_PACKAGE_TARNAME],' && \
		echo '  [$(PACKAGE_TARNAME)])' && \
		echo 'm4_define([AT_PACKAGE_VERSION],' && \
		echo '  [$(PACKAGE_VERSION)])' && \
		echo 'm4_define([AT_PACKAGE_STRING],' && \
		echo '  [$(PACKAGE_STRING)])' && \
		echo 'm4_define([AT_PACKAGE_BUGREPORT],' && \
		echo '  [$(PACKAGE_BUGREPORT)])'; \
		echo 'm4_define([AT_PACKAGE_URL],' && \
		echo '  [$(PACKAGE_URL)])'; \
	} >'$(srcdir)/package.m4'

TESTSUITE = $(srcdir)/testsuite
EXTRA_DIST = testsuite.at \
			 $(srcdir)/numbers.at $(srcdir)/convert.at \
			 $(srcdir)/package.m4 $(TESTSUITE) atlocal.in
DISTCLEANFILES = atconfig
CLEANFILES = $(libarithmos_installcheck_built_file)


.PHONY: libarithmos_check_numconf_check_rebuild \
		libarithmos_check_numconf_installcheck_rebuild
libarithmos_check_numconf_check_rebuild:
	$(MAKE) $(AM_MAKEFLAGS) clean
	$(MAKE) $(AM_MAKEFLAGS) usage$(EXEEXT)
	rm -f $(libarithmos_installcheck_built_file)

libarithmos_check_numconf_installcheck_rebuild:
	$(MAKE) $(AM_MAKEFLAGS) clean
	$(MAKE) $(AM_MAKEFLAGS) usage$(EXEEXT) \
		usage_CPPFLAGS="-I$(DESTDIR)$(includedir) $(HARDEN_CPPFLAGS)" \
		usage_LDADD="$(DESTDIR)$(libdir)/libarithmos.la" \
		usage_DEPENDENCIES="$(DESTDIR)$(libdir)/libarithmos.la"
	echo 1 > $(libarithmos_installcheck_built_file)



check-local: atconfig atlocal $(TESTSUITE)
	test ! -f $(libarithmos_installcheck_built_file) || \
		$(MAKE) $(AM_MAKEFLAGS) libarithmos_check_numconf_check_rebuild
	$(SHELL) '$(TESTSUITE)' $(TESTSUITEFLAGS)

installcheck-local: atconfig atlocal $(TESTSUITE)
	test -f "$(libarithmos_installcheck_built_file)" || \
		$(MAKE) $(AM_MAKEFLAGS) libarithmos_check_numconf_installcheck_rebuild
	$(SHELL) '$(TESTSUITE)' $(TESTSUITEFLAGS)
#	$(SHELL) '$(TESTSUITE)' AUTOTEST_PATH='$(DESTDIR)$(bindir)' \
#		$(TESTSUITEFLAGS)

clean-local:
	test ! -f '$(TESTSUITE)' || \
		$(SHELL) '$(TESTSUITE)' --clean

$(srcdir)/numbers.at:
$(srcdir)/convert.at:


AUTOM4TE = $(SHELL) $(top_srcdir)/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITE): $(srcdir)/testsuite.at $(srcdir)/numbers.at \
			  $(srcdir)/convert.at $(srcdir)/package.m4
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $@.at
	mv $@.tmp $@

