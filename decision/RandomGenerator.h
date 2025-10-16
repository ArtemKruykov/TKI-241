#pragma once

#include "Generator.h"
#include <random>

namespace miit::algebra
{
    /**
    * @brief Генератор случайных чисел в заданном диапазоне
    */
    class RandomGenerator : public Generator
    {
    private:
        std::uniform_int_distribution<int> distribution;
        std::mt19937 generator;

    public:
        /**
        * @brief Конструктор генератора случайных чисел
        * @param min минимальное значение
        * @param max максимальное значение
        */
        RandomGenerator(int min, int max);

        /**
        * @brief Генерирует случайное число
        * @return случайное число в диапазоне [min, max]
        */
        int generate() override;
    };
}