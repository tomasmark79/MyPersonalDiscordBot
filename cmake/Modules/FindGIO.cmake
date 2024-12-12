find_package(PkgConfig)
pkg_check_modules(GIO REQUIRED gio-2.0)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GIO DEFAULT_MSG GIO_FOUND)
