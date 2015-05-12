#ifndef PROTO_LAYOUT_H
#define PROTO_LAYOUT_H

namespace Proto {

enum class RenderType;
enum class Textures;

/*!
 *\brief Layout class
 * Implements the Layout table from database.
 * After read from database, used to link different
 * game objects. Its not possible to construct RenderObjects
 * directly when reading layout table because LayoutFile doesnt have any
 * clue outside of its scope. RenderObject construction reuquires already
 * constructed game objects. MapObjects, EventObjects are retrieved from
 * World class, Decorations and Layout is read by Renderer.
 *
 */
class Layout {
public:
    Layout();
    Layout(int, int);
    Layout(int, int, RenderType);
    Layout(int, int, RenderType, Textures);
    Layout(int, int, RenderType, Textures, int);

    /*!
     *\brief
     * Copy constructing Layout.
     */
    Layout(const Layout &cp) :
        id{ cp.id }, obj_type{ cp.obj_type },
        obj_id{ cp.obj_id }, texture{ cp.texture },
        priority{ cp.priority }
    { }

    Layout &operator=(const Layout &cp)
    {
        id = cp.id;
        obj_type = cp.obj_type;
        obj_id = cp.obj_id;
        texture = cp.texture;
        priority = cp.priority;

        return *this;
    }

    int get_id() const { return id; }
    int get_obj_id() const { return obj_id; }
    int get_priority() const { return priority; }

    RenderType get_render_type() const;
    Textures get_texture() const;

private:
    int id, obj_id, priority;
    RenderType obj_type;
    Textures texture;
};

}


#endif