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
	/bin/rm -f libfdata.h
	/bin/rm -f libfdata/definitions.h
	/bin/rm -f libfdata/features.h
	/bin/rm -f libfdata/types.h
	/bin/rm -f Makefile

