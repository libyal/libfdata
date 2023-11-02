include_HEADERS = \
	libfdata.h

pkginclude_HEADERS = \
	libfdata/definitions.h \
	libfdata/error.h \
	libfdata/extern.h \
	libfdata/features.h \
	libfdata/types.h

EXTRA_DIST = \
	libfdata.h.in \
	libfdata/definitions.h.in \
	libfdata/features.h.in \
	libfdata/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libfdata.h
	-rm -f libfdata/definitions.h
	-rm -f libfdata/features.h
	-rm -f libfdata/types.h
	-rm -f Makefile

