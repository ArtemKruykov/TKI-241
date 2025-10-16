#include "RandomGenerator.h"

miit::algebra::RandomGenerator::RandomGenerator(int min, int max)
    : generator(std::mt19937(std::random_device{}()))
    , distribution(std::uniform_int_distribution<int>(min, max))
{
}

int miit::algebra::RandomGenerator::generate()
{
    return distribution(generator);
}