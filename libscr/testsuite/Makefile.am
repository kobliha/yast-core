#
# Makefile.am for core/libscr/testsuite
#

AM_CXXFLAGS = -DY2LOG=\"libscr\"

AM_CPPFLAGS =						\
	-I$(top_srcdir)/libycp/src/include		\
	-I$(top_srcdir)/liby2/src/include		\
	-I$(srcdir)/../src/include			\
	${Y2UTIL_CFLAGS}

noinst_PROGRAMS = runscr
runscr_SOURCES = runscr.cc
runscr_LDADD = ${AGENT_LIBADD}

PACKAGE = libscr
AUTOMAKE_OPTIONS = dejagnu
export Y2DISABLELANGUAGEPLUGINS = 1

clean-local:
	rm -f tmp.err.* tmp.out.* ycp.log ycp.sum site.exp \
	libycp.log libycp.sum site.bak

EXTRA_DIST = README
