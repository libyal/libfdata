#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libfdata/.libs/libfdata.1.dylib && test -f ./pyfdata/.libs/pyfdata.so
then
	install_name_tool -change /usr/local/lib/libfdata.1.dylib ${PWD}/libfdata/.libs/libfdata.1.dylib ./pyfdata/.libs/pyfdata.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

