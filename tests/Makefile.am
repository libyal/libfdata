AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBFDATA_DLL_IMPORT@

TESTS = \
	test_btree.sh \
	test_list.sh \
	test_range_list.sh \
	test_vector.sh

check_SCRIPTS = \
	test_btree.sh \
	test_list.sh \
	test_range_list.sh \
	test_runner.sh \
	test_vector.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fdata_test_btree \
	fdata_test_list \
	fdata_test_range_list \
	fdata_test_vector

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

