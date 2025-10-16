#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
    * @brief Реализация задания 3: создание новой матрицы по специальному алгоритму
    */
    class Task3Exercise : public Exercise
    {
    public:
        using Exercise::Exercise;

        void Task1() override {}
        void Task2() override {}

        /**
        * @brief Создание новой матрицы: m[i] = -p[i] * (i+1) для внутренних элементов
        * @return новая матрица
        */
        std::unique_ptr<Matrix> Task3() override;
    };
}