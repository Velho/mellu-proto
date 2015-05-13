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

    /*!
     *\brief
     * Set's the Layout index that is used by DB table.
     */
    void set_id(int i) { id = i; }

    /*!
     *\brief
     * Returns table index.
     */
    int get_id() const { return id; }
    /*!
     *\brief
     * Returns object's id the texture belongs to.
     */
    int get_obj_id() const { return obj_id; }
    /*!
     *\brief
     * Returns priority on which order the Layouts are rendered.
     */
    int get_priority() const { return priority; }

    /*!
     *\brief
     * Returns render type aka which object obj_id is pointing to.
     */
    RenderType get_render_type() const;
    /*!
     *\brief
     * Returns enumeration of Texture selected.
     */
    Textures get_texture() const;

private:
    int id, obj_id, priority;
    RenderType obj_type;
    Textures texture;
};

}


#endif
