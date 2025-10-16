#include "IStreamGenerator.h"

miit::algebra::IStreamGenerator::IStreamGenerator(std::istream& in)
    : in(in)
{
}

int miit::algebra::IStreamGenerator::generate()
{
    int value = 0;
    in >> value;
    return value;
}