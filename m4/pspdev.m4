dnl
dnl AC_PSPDEV_PATH()
dnl
dnl Check for a valid pspdev installation.

AC_DEFUN([AC_PSPDEV_PATH],
[
  AC_ARG_WITH(pspdev,
              [  --with-pspdev=DIR       Path where the pspdev toolchain is installed (default is $PSPDEV)],
              pspdev="$withval", pspdev="$PSPDEV")

  AC_ARG_ENABLE([sonystubs],
    [AS_HELP_STRING([--disable-sonystubs], [Don't build Sony stub libraries])])

  AC_ARG_ENABLE([psp-graphics],
    [AS_HELP_STRING([--disable-psp-graphics], [Don't build graphics libraries])])

  AC_ARG_ENABLE([psp-libc],
    [AS_HELP_STRING([--disable-psp-libc], [Don't build PSP libc])])

  AC_MSG_CHECKING(for pspdev)
  if test x$pspdev = x ; then
     # If there's no $PSPDEV environment variable, find out where psp-gcc lives (it should be on the $PATH).
     psp_gcc_path=`which psp-gcc`
     if test x$psp_gcc_path = x ; then
        AC_MSG_ERROR(can't find the pspdev toolchain.  Use --with-pspdev or set PSPDEV)
     fi
     # Strip both the /psp-gcc and /bin portions from the path.
     pspdev=`echo $psp_gcc_path | sed 's/\/psp-gcc//' | sed 's/\/bin//'`
  fi
  AC_MSG_RESULT($pspdev)

  PSPDEV="$pspdev"
  AC_SUBST(PSPDEV)

  # Fill out a few common directories for things that need it.
  # Note: if we ever decide to support more than just the "psp" prefix, these will have to be updated.
  pspdev_includedir="$pspdev/psp/include"
  pspdev_libdir="$pspdev/psp/lib"
  PSPDEV_INCLUDEDIR="$pspdev_includedir"
  PSPDEV_LIBDIR="$pspdev_libdir"
  AC_SUBST(PSPDEV_INCLUDEDIR)
  AC_SUBST(PSPDEV_LIBDIR)

  AM_CONDITIONAL([SONYSTUBS], [test x$enable_sonystubs != xno])
  AM_CONDITIONAL([PSP_GRAPHICS], [test x$enable_psp_graphics != xno])
  AM_CONDITIONAL([PSP_LIBC], [test x$enable_psp_libc != xno])
])

dnl Check for a tool prefixed with "psp-".
dnl __PSPDEV_CHECK_TOOL(VARIABLE, PREFIX, PROG-TO-CHECK-FOR[, VALUE-IF-NOT-FOUND [, PATH]])
AC_DEFUN([__PSPDEV_CHECK_TOOL],
[
  pspdev_tool_prefix="psp-"
  AC_CHECK_PROG($1, ${pspdev_tool_prefix}$2, ${pspdev_tool_prefix}$2, $3, $4)
])

dnl
dnl AC_PSPDEV_TOOLCHAIN()
dnl
dnl Make sure all of the required pspdev tools exist.
dnl TODO: This could be made more robust just in case someone installs the tools wihthout
dnl the psp- prefix.  That's highly unlikely though.

AC_DEFUN([AC_PSPDEV_TOOLCHAIN],
[
  __PSPDEV_CHECK_TOOL(PSP_CC, gcc, psp-gcc)
  __PSPDEV_CHECK_TOOL(PSP_CXX, g++, psp-g++)
  __PSPDEV_CHECK_TOOL(PSP_AS, as, psp-as)
  __PSPDEV_CHECK_TOOL(PSP_LD, ld, psp-ld)
  __PSPDEV_CHECK_TOOL(PSP_AR, ar, psp-ar)
  __PSPDEV_CHECK_TOOL(PSP_NM, nm, psp-nm)
  __PSPDEV_CHECK_TOOL(PSP_RANLIB, ranlib, psp-ranlib)
])
