#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
    * @brief Реализация задания 2: вставка числа K после нечетных элементов, содержащих цифру K
    */
    class Task2Exercise : public Exercise
    {
    private:
        int k;

    public:
        /**
        * @brief Конструктор задания 2
        * @param matrix матрица для обработки
        * @param generator генератор значений
        * @param k число K для вставки
        */
        Task2Exercise(std::unique_ptr<Matrix> matrix, std::unique_ptr<Generator> generator, int k);

        /**
        * @brief Вставка числа K после нечетных элементов, содержащих цифру K
        */
        void Task2();
    };
}