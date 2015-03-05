#ifndef PROTO_DATABASE_H
#define PROTO_DATABASE_H

#include <string>
#include <functional>

#include <sqlite3.h>

namespace Proto {

/*!
 *\brief
 * Abstraction between physical database on
 * the disk. Provides simple interface for all
 * tables which the game uses. 
 *
 * https://github.com/iwongu/sqlite3pp/blob/master/src/sqlite3pp.h
 * Uses neat trick to get specified type out of the Row using
 * template as the second argument for get(.., T). Compiler can't
 * tell which method to overload so this fixes that problem.
 *
 * MSVC prolly yells about non-const ref's.
 */
class Database {
public:
    Database(std::string);
    ~Database();

    /*!
     *\brief
     * Alias for function pointer.
     */
    using db_callback_t = int(void*, int, char**, char**);

    int get_result() { return result; }
    //std::function<int*(void*, int, char**, char **)> callback;

    /*!
     *\brief
     * Executes query against database.
     *\param std::string
     * Sql query to be executed.
     */
    void exec(std::string);
    /*!
     *\brief
     * Executes query against database.
     * Overloaded taking callback.
     *\param std::string
     * Sql query
     *\param db_callback_t
     * Function pointer.
     */
    void exec(std::string, db_callback_t);

private:
    friend class Query;

    std::string db_file;
    int result;
    sqlite3 *database;   
};

/*!
 * \brief The Query class
 * Queries over the Sql statement. Current implementation
 * is rough wrapper around the sqlite3 functions.
 * There is 2 possbile ways to operate on class Query;
 * 1. Hand made loops and use get_row() to retrieve data.
 * 2. Use iterate(..) and provide callback which handles the data.
 *
 * Query class requires the usage of sqlite3 defined macros like
 * SQLITE_DONE, SQLITE_OK, SQLITE_ROW, etc.
 *
 * TODO Implement iterator.
 */
class Query {
public:
    Query(Database &db, std::string sql);
    ~Query();

    /*!
     * \brief The Row class
     * Represents specific row in the table.
     * You can retrieve specific data out of the Row
     * with Row's methods.
     */
    class Row {
    public:
        /*!
         * \brief Row
         * Row Constructor. This acts as default constructor atm.
         * Class member functions would return crap without valid pointer.
         */
        Row(sqlite3_stmt*);

        Row(const Row&); ///< Copy constructor.
        Row &operator=(const Row&); ///< Copy assignment.

        /*!
         * \brief get_text
         * Returns string from rows column.
         * \param
         * Index to the column(Max value column_count).
         * \return
         * String value of the columns data.
         */
        std::string get_text(int);
        /*!
         * \brief get_double
         * Returns double from rows column.
         * \param
         * Index to the column(Max value column_count).
         * \return
         * Double value from the columns data.
         */
        double get_double(int);
        /*!
         * \brief get_int
         * Returns int from rows column.
         * \param
         * Index to the column(Max value column_count).
         * \return
         * Int value of the columns data.
         */
        int get_int(int);

    private:
        sqlite3_stmt *stmt;
    };

    /*!
     * \brief step
     * Steps to the next row.
     * \return
     *
     */
    int step();
    /*!
     * \brief reset
     * \return
     */
    int reset();

    /*!
     * \brief get_column_count
     * Returns the column count of the statement.
     * Example: SELECT y, x FROM table; <= Returns 2.
     * \return
     * Amount of columns.
     */
    std::size_t get_column_count() const;

    using callback = std::function<void (Query::Row)>; ///< Alias for function object.

    /*!
     * \brief iterate
     * Loops over the statement and calls the callback for each row.
     */
    void iterate(callback);

    /*!
     * \brief get_row
     * Constructs Row out of the statement.
     * \return
     * Returns Row object to retrieve data out of it.
     */
    Query::Row get_row();

private:
    Database &database;
    std::string sql;
    sqlite3_stmt *stmt;

    int result;
};

}

#endif

