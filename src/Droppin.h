#ifndef PROTO_DROPPIN_H
#define PROTO_DROPPIN_H

#include "GameObject.h"

namespace Proto {

class Droppin {
public:

    static std::unique_ptr<GameObject> create_drop()
    {
        return std::unique_ptr<GameObject>{ };
    }

private:
    std::vector<std::unique_ptr<GameObject>> gobjs; ///< Lists of drop gameobjects.
};

}

#endif
