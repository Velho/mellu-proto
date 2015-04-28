#include "RandomGen.h"

namespace Proto {

RandomGen::RandomGen()
{
    std::random_device dev;
    rnd_eng.seed(dev());
}

int RandomGen::operator ()(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(rnd_eng);
}

}
