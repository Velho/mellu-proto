#ifndef PROTO_DROPPIN_H
#define PROTO_DROPPIN_H

#include "GameObject.h"
#include <array>

namespace Proto {

class Droppin {
public:
    using GObj = GameObject;
    using GObjPtr = std::unique_ptr<GObj>;

    static GObjPtr create_drop();

    void handle_input(sf::Event&);
    void update(World&);
    void draw(sf::RenderTarget&);

private:
    struct d_offsets;

    std::vector<GObjPtr> gobjs; ///< Lists of drop gameobjects.
    std::array<d_offsets*, 6> offsets;

    struct d_offsets {
        float x;
        bool allocated;
    };
};

}

#endif
