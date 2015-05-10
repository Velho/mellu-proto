#ifndef PROTO_LAYOUTFILE_H
#define PROTO_LAYOUTFILE_H

#include <vector>
#include <memory>
#include <string>

namespace Proto {

class Layout;
class Renderer;

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
 *
 * Query is pretty straight forward for few exceptions,
 * obj_id isnt tied to any sql based reference aka foreign key.
 * But everything except priority can be directly casted to
 * corresponding enum class.
 *
 * There's no specific requirement for lay_id index value so
 * it's just auto incrementally set.
 * Like obj_id, texture, etc
 * is very tightly coupled as if not textures get messed up and
 * wrong object etc.
 */
class LayoutFile {
public:
    LayoutFile(std::string file) : filename(file)
    { }

    std::vector<std::unique_ptr<Layout>> load();
    void save(Renderer&);

private:
    std::string filename;
};
}

#endif

