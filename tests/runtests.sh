#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libfdata/.libs/libfdata.1.dylib && test -f ./pyfdata/.libs/pyfdata.so;
then
	install_name_tool -change /usr/local/lib/libfdata.1.dylib ${PWD}/libfdata/.libs/libfdata.1.dylib ./pyfdata/.libs/pyfdata.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

