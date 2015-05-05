#ifndef PROTO_LAYOUTFILE_H
#define PROTO_LAYOUTFILE_H

namespace Proto {

class RenderObject;

/*!
 *\brief LayoutFile class
 * Represents Layout table from the
 * maps database.
 *
 * SQL =>
 *  CREATE TABLE layout(
 *      lay_id INTEGER PRIMARY KEY AUTOINCREMENT,
 *      obj_type INTEGER, obj_id INTEGER,
 *      texture INTEGER, priority INTEGER);
 * Query is pretty straight forward for few exceptions,
 * obj_id isnt tied to any sql based reference aka foreign key.
 * But everything except priority can be directly casted to
 * corresponding enum class.
 */
class LayoutFile {
public:

private:
};
}

#endif

