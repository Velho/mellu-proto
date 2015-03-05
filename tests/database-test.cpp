/**
 * Project : mellu-proto
 * Author : Velho @ 2015
 *
 * Simple test of the Sqlite3 wrapper class.
 * Provides efficient and flexible abstraction over
 * some nasty C functions.
 * 
 * TODO Unit or Mock library would be better though but hey atleast we have a test.
 */

#include "Database.h"

using Proto::Database;
using Proto::Query;

int main()
{
    Database db("database-test.db");
    Query qry(db, "SELECT x, y, name FROM events;");

    // Callback for the iterate(..).
    auto cb = [](Query::Row row) {
        std::cout << "x : " << row.get_double(0) << std::endl;
        std::cout << "y : " << row.get_double(1) << std::endl;
        std::cout << "name : " << row.get_text(2) << std::endl;
    };

    std::cout << "Callback test" << std::endl;
    // Loop over the rows and while callback handles the data.
    qry.iterate(cb);

    qry.reset(); // Resets the query.

    std::cout << "Loop test" << std::endl;
    // Use your own loop to loop over the rows.
    while(qry.step() == SQLITE_ROW) {
        Query::Row row(qry.get_row());

        std::cout << "x : " << row.get_double(0) << std::endl;
        std::cout << "y : " << row.get_double(1) << std::endl;
        std::cout << "name : " << row.get_text(2) << std::endl;
    }
}
