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

TESTS = \
	test_library.sh

check_SCRIPTS = \
	test_library.sh \
	test_manpage.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

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

DISTCLEANFILES = \
	Makefile \
	Makefile.in \
	notify_stream.log

