ACLOCAL_AMFLAGS = -I aclocal
ACLOCAL_FILES = aclocal/version.m4 aclocal/pspdev.m4 aclocal/ac_doxygen.m4

SUBDIRS = src tools

include aminclude.am

MOSTLYCLEANFILES = $(DX_CLEANFILES)

EXTRA_DIST =			\
	$(ACLOCAL_FILES)	\
	LICENSE			\
	VERSION			\
	$(DX_CONFIG)		\
	doc/html

dist-hook:
	rm -rf `find $(distdir)/doc/html/* -name .svn -o -name CVS`
