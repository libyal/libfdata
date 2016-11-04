AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBFDATA_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fdata_test_area \
	fdata_test_btree \
	fdata_test_error \
	fdata_test_list \
	fdata_test_range_list \
	fdata_test_support \
	fdata_test_vector

fdata_test_area_SOURCES = \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_libcstring.h \
	fdata_test_area.c \
	fdata_test_unused.h

fdata_test_area_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

fdata_test_btree_SOURCES = \
	fdata_test_btree.c \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_libcstring.h \
	fdata_test_unused.h

fdata_test_btree_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

fdata_test_error_SOURCES = \
	fdata_test_error.c \
	fdata_test_libcstring.h \
	fdata_test_libfdata.h \
	fdata_test_macros.h \
	fdata_test_unused.h

fdata_test_error_LDADD = \
	../libfdata/libfdata.la \
	@LIBCSTRING_LIBADD@

fdata_test_list_SOURCES = \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_libcstring.h \
	fdata_test_list.c \
	fdata_test_unused.h

fdata_test_list_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

fdata_test_range_list_SOURCES = \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_libcstring.h \
	fdata_test_range_list.c \
	fdata_test_unused.h

fdata_test_range_list_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

fdata_test_support_SOURCES = \
	fdata_test_libcstring.h \
	fdata_test_libfdata.h \
	fdata_test_macros.h \
	fdata_test_support.c \
	fdata_test_unused.h

fdata_test_support_LDADD = \
	../libfdata/libfdata.la \
	@LIBCSTRING_LIBADD@

fdata_test_vector_SOURCES = \
	fdata_test_libcerror.h \
	fdata_test_libfdata.h \
	fdata_test_libcstring.h \
	fdata_test_vector.c \
	fdata_test_unused.h

fdata_test_vector_LDADD = \
	../libfdata/libfdata.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

