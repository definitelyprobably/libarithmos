#AM_CXXFLAGS = $(OPTIM_CXXFLAGS) $(HARDEN_CXXFLAGS)

lib_LTLIBRARIES = libarithmos.la
libarithmos_la_CPPFLAGS = $(HARDEN_CPPFLAGS)
libarithmos_la_CXXFLAGS = $(OPTIM_CXXFLAGS) $(HARDEN_CXXFLAGS)
libarithmos_la_LDFLAGS = -version-info 0:1:0 $(HARDEN_LDFLAGS)
libarithmos_la_SOURCES = arithmos.cpp

include_HEADERS = arithmos.h arithmos.tcc
