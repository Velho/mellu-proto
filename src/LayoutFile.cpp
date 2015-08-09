#include "LayoutFile.h"
#include "Layout.h"

#include "Renderer.h"
#include "RenderObject.h"
#include "Database.h"

#include "Resources.h"

#include <sstream>

namespace Proto {

struct LayoutRow {
    int id, obj_type, obj_id;
    int texture, priority;

    /*!
     *\brief
     * Constructing full LayoutRow.
     */
    LayoutRow(int _id, int _obj_type, int _obj_id,
            int _texture, int _priority) :
                id{ _id }, obj_type{ _obj_type },
                obj_id{ _obj_id }, texture{ _texture },
                priority{ _priority }
    { }

    /*!
     *\brief
     * Constructing LayoutRow from Query::Row object containing
     * information from sql statement.
     */
    LayoutRow(Query::Row row) :
        LayoutRow(row.get_int(0), row.get_int(1),
                row.get_int(2), row.get_int(3), row.get_int(4))
    { }

    Layout get_layout()
    {
        return Layout(id, obj_id,
                static_cast<RenderType>(obj_type),
                static_cast<Textures>(texture), priority);
    }
};

std::vector<std::unique_ptr<Layout>> LayoutFile::load()
{
    Database db(filename);
    Query query(db, "SELECT lay_id, obj_type, obj_id, texture, priority FROM layout;");
    std::vector<std::unique_ptr<Layout>> results;

    query.iterate([&results](Query::Row r){
        results.emplace_back(std::unique_ptr<Layout>(
                new Layout(LayoutRow(r).get_layout())));
    });

    return results;
}

void LayoutFile::save(Renderer &renderer)
{
    Database db(filename);
    std::ostringstream sql;
    int index{ 1 };

    db.exec("DELETE FROM layout;");

    for(auto &lay : renderer.layout_objs) {
        sql << "INSERT INTO layout(lay_id, obj_type, obj_id, texture, priority) VALUES(";

        sql << index << ", "; // TODO HIGH : lay->get_id() ??
        sql << static_cast<int>(lay->get_render_type()) << ", ";
        sql << lay->get_obj_id() << ", ";
        sql << static_cast<int>(lay->get_texture()) << ", ";
        sql << lay->get_priority() << ");";

        index++; // Increment the primary key.
    }

    db.exec(sql.str());
}

}
