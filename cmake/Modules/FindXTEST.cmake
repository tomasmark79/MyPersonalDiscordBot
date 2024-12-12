find_package(PkgConfig)
pkg_check_modules(XTEST REQUIRED xtst)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(XTEST DEFAULT_MSG XTEST_FOUND)
