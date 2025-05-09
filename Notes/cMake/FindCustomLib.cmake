# FindCustomLibrary.cmake

find_path(CUSTOM_LIBRARY_INCLUDE_DIR custom_library.h)
find_library(CUSTOM_LIBRARY_LIBRARY NAMES custom_library)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CustomLibrary DEFAULT_MSG CUSTOM_LIBRARY_LIBRARY CUSTOM_LIBRARY_INCLUDE_DIR)
