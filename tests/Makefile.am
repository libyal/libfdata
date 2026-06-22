AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBFDATA_DLL_IMPORT@

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages

check_PROGRAMS = \
	fdata_test_area \
	fdata_test_cache \
	fdata_test_error \
	fdata_test_list \
	fdata_test_list_element \
	fdata_test_mapped_range \
	fdata_test_notify \
	fdata_test_range \
	fdata_test_range_list \
	fdata_test_stream \
	fdata_test_support \
	fdata_test_vector

fdata_test_area_SOURCES = \
	fdata_test_area.c \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_macros.h \
	fdata_test_memory.c fdata_test_memory.h \
	fdata_test_unused.h

fdata_test_area_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@

fdata_test_cache_SOURCES = \
	fdata_test_cache.c \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_macros.h \
	fdata_test_memory.c fdata_test_memory.h \
	fdata_test_unused.h

fdata_test_cache_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@

fdata_test_error_SOURCES = \
	fdata_test_error.c \
	fdata_test_libfdata.h \
	fdata_test_macros.h \
	fdata_test_unused.h

fdata_test_error_LDADD = \
	../libfdata/libfdata.la

fdata_test_list_SOURCES = \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_list.c \
	fdata_test_macros.h \
	fdata_test_memory.c fdata_test_memory.h \
	fdata_test_unused.h

fdata_test_list_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@

fdata_test_list_element_SOURCES = \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_list_element.c \
	fdata_test_macros.h \
	fdata_test_memory.c fdata_test_memory.h \
	fdata_test_unused.h

fdata_test_list_element_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@

fdata_test_mapped_range_SOURCES = \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_macros.h \
	fdata_test_mapped_range.c \
	fdata_test_memory.c fdata_test_memory.h \
	fdata_test_unused.h

fdata_test_mapped_range_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@

fdata_test_notify_SOURCES = \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_macros.h \
	fdata_test_notify.c \
	fdata_test_unused.h

fdata_test_notify_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@

fdata_test_range_SOURCES = \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_macros.h \
	fdata_test_memory.c fdata_test_memory.h \
	fdata_test_range.c \
	fdata_test_unused.h

fdata_test_range_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@

fdata_test_range_list_SOURCES = \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_macros.h \
	fdata_test_memory.c fdata_test_memory.h \
	fdata_test_range_list.c \
	fdata_test_unused.h

fdata_test_range_list_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@

fdata_test_stream_SOURCES = \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_macros.h \
	fdata_test_memory.c fdata_test_memory.h \
	fdata_test_stream.c \
	fdata_test_unused.h

fdata_test_stream_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@

fdata_test_support_SOURCES = \
	fdata_test_libfdata.h \
	fdata_test_macros.h \
	fdata_test_support.c \
	fdata_test_unused.h

fdata_test_support_LDADD = \
	../libfdata/libfdata.la

fdata_test_vector_SOURCES = \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_macros.h \
	fdata_test_memory.c fdata_test_memory.h \
	fdata_test_unused.h \
	fdata_test_vector.c

fdata_test_vector_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_library: \
	package.m4 \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

