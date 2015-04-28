#ifndef PROTO_RANDOMGEN_H
#define PROTO_RANDOMGEN_H

#include <random>
#include <functional>

namespace Proto {

/*!
 *\brief RandomGen class
 * Generates some Random values for different
 * needs. Can be used with different distributions and
 * devices. Currently implements simple class for rnd gen.
 *
 * TODO Implement template function for int vs real. (Tag based?)
 */
class RandomGen {
public:
    RandomGen();
    int operator()(int, int);

private:
    std::mt19937 rnd_eng;
};

}

#endif
