#include "Database.h"

#include "EventFile.h"
#include "Events.h"

#include <iostream>

namespace Proto {

/*!
 * \brief The EventObjectRow struct
 * Represents Eventobject in Row of data.
 */
struct EventObjectRow {
    double x, y, width, height;
    int evt_id, evt_table_id;

    /*!
     * \brief EventObjectRow
     * Default constructor for EventObject.
     * \param _x
     * \param _y
     * \param _width
     * \param _height
     * \param type
     * \param id
     */
    EventObjectRow(double _x, double _y,
                   double _width, double _height,
                   int eid, int id) :
        x{ _x }, y{ _y }, width{ _width }, height{ _height },
        evt_table_id{ eid }, evt_id{ id }
    { }

    /*!
     * \brief EventObjectRow
     * Make an assumption about the Query
     * and constructs the Row object. Column count < 6
     *
     * SELECT x,y,width,height,evt_type,evt_table_id FROM events;
     *
     * \param row
     */
    EventObjectRow(Query::Row row) :
        EventObjectRow(
            row.get_double(0), row.get_double(1), row.get_double(2), row.get_double(3),
            row.get_int(4), row.get_int(5))
    {
    }

    /*!
     * \brief get_event_object
     * Creates EventObject out of the member variables.
     * Used as rvalue object.
     * \return
     * By-value return EventObject which can be copied and assigned after.
     */
    EventObject get_event_object()
    {
        return EventObject(sf::Vector2f(x, y), sf::Vector2f(width, height), evt_table_id, evt_id);
    }
};

std::vector<std::unique_ptr<EventObject>> EventFile::load()
{
    Database db(filename);
    Query qry(db, "SELECT x, y, width, height, evt_table_id, evt_id FROM events;");

    std::vector<std::unique_ptr<EventObject>> e_objs; // For lambda capture list.

    qry.iterate([&e_objs](Query::Row r) {
        e_objs.emplace_back(std::unique_ptr<EventObject>(new EventObject(EventObjectRow(r).get_event_object())));
    }); // Loop the data.

    return e_objs;
}

void EventFile::save(Events &evt)
{
    Database db(filename);
    std::ostringstream ins_sql;

    db.exec("DELETE FROM events;"); // Drop the table.

    for(auto &obj : evt.evt_objs) {
        // Insert query.
        ins_sql << "INSERT INTO events(evt_id, x, y, width, height, evt_table_id) VALUES(";
        ins_sql << obj->get_evt_id() << ", " << obj->get_position().x << ", " << obj->get_position().y << ", ";
        ins_sql << obj->get_size().x << ", " << obj->get_size().y << ", ";
        ins_sql << obj->get_evt_table_id() << ");";
    }

    // Execute query.
    db.exec(ins_sql.str());
}
}
