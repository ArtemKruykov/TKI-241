#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
    * @brief Реализация задания 1: замена первого элемента, кратного 5, на 0
    */
    class Task1Exercise : public Exercise
    {
    public:
        using Exercise::Exercise;

        /**
        * @brief Замена первого элемента, кратного 5, на 0
        */
        void Task1() override;

        void Task2() override {}

        std::unique_ptr<Matrix> Task3() override { return nullptr; }
    };
}