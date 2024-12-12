find_package(PkgConfig)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GTK3 DEFAULT_MSG GTK3_FOUND)
