find_package(PkgConfig)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLIB DEFAULT_MSG GLIB_FOUND)
