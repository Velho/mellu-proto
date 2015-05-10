#include "Database.h"

#include "DecorationFile.h"
#include "Decoration.h"

#include "Renderer.h"

#include <sstream>

namespace Proto {

struct DecorationRow {
	int id;
    float x, y;

    /*!
     *\brief DecorationRow ctor
     * Fully constructs the DecorationRow object.
     */
    DecorationRow(int _id, float _x, float _y) :
        id{ _id }, x{ _x }, y{ _y }
    { }

    /*!
     *\brief DecorationRow
     * Constructs DecorationRow object out of Query::Row object.
     *\param r Row that contains data of the Query's statement.
     */
    DecorationRow(Query::Row r) :
        DecorationRow(r.get_int(0), r.get_double(1),
            r.get_double(2))
    { }

    /*!
     *\brief
     * Constructs Decoration object on the stack based on DecorationRow's data.
     */
    Decoration get_decoration()
    {
        return Decoration(id, sf::Vector2f(x, y));
    }
};

std::vector<std::unique_ptr<Decoration>> DecorationFile::load()
{
	Database db(filename);
    Query query(db, "SELECT deco_id, x, y, FROM decoration;");

    // Compiler *SHOULD* optimize this and return as rvalue..
    std::vector<std::unique_ptr<Decoration>> results;

    query.iterate([&results](Query::Row r) {
        results.emplace_back(std::unique_ptr<Decoration>(new Decoration(DecorationRow(r).get_decoration())));
    });

    return results;
}

void DecorationFile::save(Renderer &renderer)
{
	Database db(filename);
	std::ostringstream sql;

	db.exec("DELETE FROM decoration;");

	int idx{ 1 };
	for(auto &obj : renderer.deco_objs) {
        sql << "INSERT INTO decoration(evt_id, x, y) VALUES(";

        sql << obj->get_id() << ", ";
        sql << obj->get_position().x << ", ";
        sql << obj->get_position().y << ");";
	}

	db.exec(sql.str());
}

}
