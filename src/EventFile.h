#ifndef PROTO_EVENTFILE_H
#define PROTO_EVENTFILE_H

namespace Proto {

/*!
 * \brief The EventFile class
 * Represents physical file on hard drive.
 * data/events
 */
class EventFile {
public:
    EventFile();
    ~EventFile();

    void load();
    void save();

private:

};
}


#endif
