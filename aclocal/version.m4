dnl
dnl AC_PSPSDK_VERSION()
dnl
dnl Determine the pspsdk package version.

AC_DEFUN([AC_PSPSDK_VERSION],
[
  AC_BEFORE([$0], [AM_INIT_AUTOMAKE])

  AC_MSG_CHECKING([for pspsdk version])
  AS_IF([test -r "${srcdir}/aclocal/version.m4"],
        [],
        [AC_MSG_ERROR([Unable to find aclocal/version.m4])])
  AS_IF([test -r "${srcdir}/VERSION"],
        [],
	[AC_MSG_ERROR([Unable to find VERSION])])
  pspsdk_version=`cat "${srcdir}/VERSION"`
  AC_MSG_RESULT($pspsdk_version)
])
