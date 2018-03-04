# - Try to find Cairomm 1.0
# Once done, this will define
#
#  Cairomm_FOUND - system has Cairomm
#  Cairomm_INCLUDE_DIRS - the Cairomm include directories
#  Cairomm_LIBRARIES - link these to use Cairomm

include(./cmake/LibFindMacros.cmake)

# Dependencies
libfind_package(Cairomm Cairo)
libfind_package(Gtkmm gtk+)
libfind_package(Glibmm glib)
#libfind_package(Sigcpp sigc++)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(Cairomm_PKGCONF cairomm-1.0)
libfind_pkg_check_modules(Gtkmm_PKGCONF gtkmm-3.0)
libfind_pkg_check_modules(Glibmm_PKGCONF glibmm-2.4)
libfind_pkg_check_modules(Sigcpp_PKGCONF sigc++-2.0)

# Main include dir
find_path(Cairomm_INCLUDE_DIR
  NAMES cairomm/cairomm.h
  PATHS ${Cairomm_PKGCONF_INCLUDE_DIRS}
  PATH_SUFFIXES cairomm-1.0
  )

find_path(Gtkmm_INCLUDE_DIR
  NAMES gtkmm.h
  PATHS ${Gtkmm_PKGCONF_INCLUDE_DIRS}
  PATH_SUFFIXES gtkmm-3.0
)

find_path(Glibmm_INCLUDE_DIR
  NAMES glibmm.h
  PATHS ${Gtkmm_PKGCONF_INCLUDE_DIRS}
  PATH_SUFFIXES glibmm-2.4
)

find_path(Sigcpp_INCLUDE_DIR
  NAMES sig++/sigc++.h
  PATHS ${Sigcpp_PKGCONF_INCLUDE_DIRS}
  PATH_SUFFIXES sigc++-2.0
)

libfind_library(Cairomm cairomm 1.0)
libfind_library(Gtkmm gtkmm 3.0)
libfind_library(Glibmm glibmm 2.4)
libfind_library(Sigcpp sigc++ 2.0)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(Cairomm_PROCESS_INCLUDES Cairomm_INCLUDE_DIR Cairo_INCLUDE_DIRS)
set(Cairomm_PROCESS_LIBS Cairomm_LIBRARY Cairo_LIBRARIES)
libfind_process(Cairomm)

set(Gtkmm_PROCESS_INCLUDES Gtkmm_INCLUDE_DIR Gtk_INCLUDE_DIRS)
set(Gtkmm_PROCESS_LIBS     Gtkmm_LIBRARY     Gtk_LIBRARIES)
libfind_process(Gtkmm)

set(Glibmm_PROCESS_INCLUDES Glibmm_INCLUDE_DIR Glib_INCLUDE_DIRS)
set(Glibmm_PROCESS_LIBS     Glibmm_LIBRARY     Glib_LIBRARIES)
libfind_process(Glibmm)

set(Sigcpp_PROCESS_INCLUDES Sigcpp_INCLUDE_DIR Sigcpp_INCLUDE_DIRS)
set(Sigcpp_PROCESS_LIBS     Sigcpp_LIBRARY     Sigcpp_LIBRARIES)
libfind_process(Sigcpp)




set(Cairomm_INCLUDE_DIRS ${Cairomm_PKGCONF_INCLUDE_DIRS})
set(Gtkmm_INCLUDE_DIRS   ${Gtkmm_PKGCONF_INCLUDE_DIRS})
set(Glibmm_INCLUDE_DIRS  ${Glibmm_PKGCONF_INCLUDE_DIRS})
set(Sigcpp_INCLUDE_DIRS  ${Sigcpp_PKGCONF_INCLUDE_DIRS})
