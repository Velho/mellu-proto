#ifndef PROTO_EVENTFILE_H
#define PROTO_EVENTFILE_H

#include <string>
#include <vector>
#include <memory>

namespace Proto {

class Events;
class EventObject;

/*!
 * \brief The EventFile class
 * Manages Event table in the map file format.
 *
 * CREATE TABLE events(
 *      evt_id INTEGER PRIMARY KEY AUTOINCREMENT,
 *      x float, y float, width float, height float,
 *      evt_type int, evt_table_id int);
 *
 * Insert evt_table_id by hand because there's no ui currently that does it.
 */
class EventFile {
public:
    /*!
     * \brief EventFile
     * Constructs EventFile class with specific database.
     * \param file
     * String to Database file.
     */
    EventFile(std::string file) :
        filename(file), evt_counter{ 0 }
    { }
    ~EventFile() { }

    std::vector<std::unique_ptr<EventObject>> load();
    void save(Events&);
    friend void save(Events&);

    /*!
     * \brief get_evtc
     * Amount of event objects loaded from the file.
     * \return
     * evt_counter
     */
    int get_evtc() const { return evt_counter; }

private:
    std::string filename;
    int evt_counter;
};
}


#endif
