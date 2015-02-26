# Searches for Sqlite3
# Velho @ 2014
# Tested under Linux(TODO Win support).


# Path as /usr/include??
# Headers
find_path(Sqlite3_INCLUDE_DIR sqlite3.h)
# Libs
find_library(Sqlite3_LIBRARY sqlite3 libsqlite3)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Sqlite3 
    DEFAULT_MSG
    Sqlite3_LIBRARY
    Sqlite3_INCLUDE_DIR)
