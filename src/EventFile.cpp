#include "Database.h"

#include "EventFile.h"
#include "Events.h"

#include <sstream>
#include <iostream>

namespace Proto {

/*!
 * \brief The EventObjectRow struct
 * Represents Eventobject in Row of data.
 */
struct EventObjectRow {
    double x, y, width, height;
    int evt_type, evt_table_id;

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
                   int type, int id) :
        x{ _x }, y{ _y }, width{ _width }, height{ _height }, evt_type{ type }, evt_table_id{ id }
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
        return EventObject(sf::Vector2f(x, y), sf::Vector2f(width, height),
                           static_cast<EventObject::EventType>(evt_type), evt_table_id);
    }
};

std::vector<std::unique_ptr<EventObject>> EventFile::load()
{
    Database db(filename);
    Query qry(db, "SELECT x,y,width,height,evt_type,evt_table_id FROM events;");

    std::vector<std::unique_ptr<EventObject>> e_objs; // For lambda capture list.

    // Handle the row.
    auto row = [&e_objs, this](Query::Row r) {
        e_objs.emplace_back(new EventObject(EventObjectRow(r).get_event_object()));
        this->evt_counter++;
    };

    qry.iterate(row); // Loop the data.

    std::cout << "evt_counter : " << evt_counter << std::endl;

    return e_objs;
}

void EventFile::save(Events &evt)
{
    Database db(filename);
    std::stringstream sql_strm;

    sql_strm << "INSERT INTO events(x, y, width, height, evt_type, evt_table_id) VALUES(";

    // if i < counter => UPDATE, i > INSERT.
    for(int i = 0; i < evt.evt_objs.size(); i++) {

    }
}

}
