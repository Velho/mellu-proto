#ifndef PROTO_DECOFILE_H
#define PROTO_DECOFILE_H

#include <string>
#include <vector>
#include <memory>

namespace Proto {

class Decoration;
class Renderer;

/*!
 *\brief The DecorationFile class
 * Loads the Decorations from the file.
 * Decoration keeps the different type with
 * the object, but the most important question
 * is how the priority is saved and handled?
 * Compiled time or runtime loaded from file?
 * 
 * Decoration provides the graphical layout for
 * the game which means that Decorations doesnt
 * affect the physics engine in any way.
 *
 * SQL =>
 *  CREATE TABLE decoration(
 *      deco_id INTEGER PRIMARY KEY AUTOINCREMENT,
 *      x float, y float, width float, height float);
 */
class DecorationFile {
public:
    DecorationFile(std::string fn) :
        filename(fn)
    { }

    /*!
     *\brief
     * Decorations are returned as vector but after
     * Renderer has fully been initialized, decorations
     * gets passed along as RenderObject.
     */
    std::vector<std::unique_ptr<Decoration>> load();
    void save(Renderer&);

private:
    std::string filename;


};

}

#endif
