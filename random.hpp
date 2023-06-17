#ifndef D_RANDOM_HPP
#define D_RANDOM_HPP

#include <random>

#include "types.hpp"

class rdm::types::RandomGenerator
{
    public:
        /*** Constructors ***/

        // Initialize with seed
        RandomGenerator(std::default_random_engine::result_type seed);

        // Get random double
        double getRandomDouble(double min, double max);

        // Get random int
        int getRandomInt(int min, int max);

    private:
        std::default_random_engine engine;
};


#endif