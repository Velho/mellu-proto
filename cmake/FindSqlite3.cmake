# Searches for Sqlite3

find_path(Sqlite3_INCLUDE_DIR sqlite3.h)

find_library(Sqlite3_LIBRARY sqlite3 libsqlite3)

find_package_handle_standard_args(Sqlite3 
    DEFAULT_MSG
    Sqlite3_LIBRARY
    Sqlite3_INCLUDE_DIR)
