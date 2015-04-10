#include "Database.h"
#include <boost/lexical_cast.hpp>

namespace Proto {

Database::Database(std::string filename) :
    db_file(filename)
{
    result = sqlite3_open(filename.c_str(), &database);
}

Database::~Database()
{
    sqlite3_close(database);
}

void Database::exec(std::string sql)
{
    sqlite3_exec(database, sql.c_str(), nullptr, nullptr, nullptr);
}

void Database::exec(std::string sql, Database::db_callback_t cb)
{
    sqlite3_exec(database, sql.c_str(), cb, nullptr, nullptr);
}

Query::Query(Database &db, std::string s) :
    database{ db }, sql(s)
{
    result = sqlite3_prepare_v2(db.database, sql.c_str(), -1, &stmt, NULL);
}

Query::~Query()
{
    sqlite3_finalize(stmt);
}

Query::Row::Row(sqlite3_stmt *s) : stmt{ s }
{ }

Query::Row::Row(const Query::Row &cp) :
    stmt{ cp.stmt }
{ }

Query::Row &Query::Row::operator=(const Query::Row &cp)
{
    stmt = cp.stmt;

    return *this;
}

std::string Query::Row::get_text(int id)
{
    return std::string(reinterpret_cast<const char*>(
                           sqlite3_column_text(stmt, id)));
}

double Query::Row::get_double(int id)
{
    return sqlite3_column_double(stmt, id);
}

int Query::Row::get_int(int id)
{
    return sqlite3_column_int(stmt, id);
}

int Query::step()
{
    return result = sqlite3_step(stmt);
}

int Query::reset()
{
    return result = sqlite3_reset(stmt);
}

std::size_t Query::get_column_count() const
{
    return sqlite3_column_count(stmt);
}

Query::Row Query::get_row()
{
    return Row(stmt);
}

void Query::iterate(callback cb)
{
    // No iteration without callback.
    if(!cb)
        return;

    while(step() == SQLITE_ROW)
        cb(get_row());
}

}
