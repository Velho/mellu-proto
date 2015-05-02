#ifndef PROTO_DECOFILE_H
#define PROTO_DECOFILE_H

namespace Proto {

/*!
 *\brief The DecorationFile class
 * Loads the Decorations from the file.
 * Decoration keeps the different type with
 * the object, but the most important question
 * is how the priority is saved and handled?
 * Compiled time or runtime loaded from file?
 * 
 * Decoration provides the graphical layout for
 * the game
 */
class DecorationFile {
public:
    DecorationFile();
    ~DecorationFile();

    void load();
    void save();

private:
};

}

#endif
