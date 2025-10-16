#pragma once

namespace miit::algebra
{
    /**
    * @brief Абстрактный генератор значений для заполнения матрицы
    */
    class Generator
    {
    public:
        /**
        * @brief Виртуальный деструктор
        */
        virtual ~Generator() = default;

        /**
        * @brief Генерирует следующее значение
        * @return сгенерированное значение
        */
        virtual int generate() = 0;
    };
}