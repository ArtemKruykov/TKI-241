#pragma once
#include "Matrix.h"
#include "Generator.h"
#include <memory>

namespace miit::algebra
{
    /**
    * @brief Абстрактный класс для выполнения заданий над матрицей
    */
    class Exercise
    {
    protected:
        std::unique_ptr<Matrix> matrix;
        std::unique_ptr<Generator> generator;

    public:
        /**
        * @brief Конструктор упражнения
        * @param matrix матрица для обработки
        * @param generator генератор значений
        */
        Exercise(std::unique_ptr<Matrix> matrix, std::unique_ptr<Generator> generator);

        /**
        * @brief Виртуальный деструктор
        */
        virtual ~Exercise() = default;

        /**
        * @brief Виртуальный метод для выполнения задания 1
        */
        virtual void Task1() = 0;

        /**
        * @brief Виртуальный метод для выполнения задания 2
        */
        virtual void Task2() = 0;

        /**
        * @brief Виртуальный метод для выполнения задания 3
        */
        virtual std::unique_ptr<Matrix> Task3() = 0;

        /**
        * @brief Возвращает строковое представление матрицы
        * @return строка с матрицей
        */
        std::string get_matrix_string() const;

        /**
        * @brief Возвращает константную ссылку на данные матрицы
        * @return константная ссылка на вектор данных
        */
        const std::vector<int>& get_data() const;

        /**
        * @brief Возвращает размер матрицы
        * @return размер матрицы
        */
        size_t size() const;
    };
}