# serial 1   libarithmos.m4
# 
# An M4 macro file that defines the macro `AV_LIBARITHMOS', which is used
# to test whether the libarithmos library is installed on your system.
#
# Copyright (c) Karta Kooner, 2020.
#
# You are free to use, modify and distribute this file as you wish without
# royalty or prior permission as long as the above copyright notice and this
# notice are preserved.
#
AC_DEFUN([AV_LIBARITHMOS],
[
    AC_LANG_PUSH([C++])
    LIBS_SAVED="$LIBS"
    LIBS="$LIBS -lnumconf"
    AC_MSG_CHECKING(if the libarithmos library is installed)
    AC_LINK_IFELSE([AC_LANG_PROGRAM([[@%:@include <arithmos.h>]],
                                    [[Arithmos::Data d;]])],
                   [AC_MSG_RESULT([yes])
				    have_libarithmos=yes],
                   [AC_MSG_RESULT([no])
                    AC_MSG_FAILURE([libarithmos library not installed])]
    )
    AC_LANG_POP([C++])
    LIBS="$LIBS_SAVED"
	AS_IF([test x"$have_libarithmos" = xyes],
	      [LIBARITHMOS_LIB="-larithmos"],
		  [LIBARITHMOS_LIB=""])
	AC_SUBST([LIBARITHMOS_LIB])
])
