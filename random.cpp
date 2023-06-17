#include "random.hpp"

rdm::types::RandomGenerator::RandomGenerator(std::default_random_engine::result_type seed):
    engine(seed)
{
}

double rdm::types::RandomGenerator::getRandomDouble(double min, double max)
{
    static std::uniform_real_distribution<double> distr;

    const decltype(distr)::param_type new_params {min, max};

    return distr(engine, new_params);
}

int rdm::types::RandomGenerator::getRandomInt(int min, int max) 
{
    static std::uniform_int_distribution<int> distr;

    const decltype(distr)::param_type new_params {min, max};

    return distr(engine, new_params);
}