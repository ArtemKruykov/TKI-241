#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Generator.h"

namespace miit::algebra
{
    /**
    * @brief Одномерная матрица (массив) с дополнительными операциями
    */
    class Matrix
    {
    private:
        std::vector<int> data;

    public:
        // Конструкторы по умолчанию
        Matrix() = default;
        Matrix(const Matrix&) = default;
        Matrix(Matrix&&) = default;
        ~Matrix() = default;

        /**
        * @brief Конструктор с заданным размером
        * @param size размер матрицы
        */
        explicit Matrix(size_t size);

        /**
        * @brief Конструктор из вектора
        * @param elements вектор элементов
        */
        explicit Matrix(const std::vector<int>& elements);

        /**
        * @brief Заполняет матрицу значениями из генератора
        * @param generator генератор значений
        */
        void fill(std::unique_ptr<Generator> generator);

        /**
        * @brief Возвращает строковое представление матрицы
        * @return строка с элементами матрицы
        */
        std::string to_string() const;

        /**
        * @brief Возвращает размер матрицы
        * @return размер матрицы
        */
        size_t size() const;

        /**
        * @brief Возвращает константную ссылку на внутренние данные
        * @return константная ссылка на вектор данных
        */
        const std::vector<int>& get_data() const;

        // Операторы
        Matrix& operator=(const Matrix&) = default;
        Matrix& operator=(Matrix&&) = default;

        /**
        * @brief Оператор сдвига влево (добавление элемента в начало)
        * @param value значение для добавления
        * @return ссылка на текущий объект
        */
        Matrix& operator<<(int value);

        /**
        * @brief Оператор сдвига вправо (извлечение элемента из начала)
        * @param value ссылка для сохранения извлеченного значения
        * @return ссылка на текущий объект
        */
        Matrix& operator>>(int& value);

        /**
        * @brief Оператор доступа по индексу
        * @param index индекс элемента
        * @return ссылка на элемент
        */
        int& operator[](size_t index);

        /**
        * @brief Константный оператор доступа по индексу
        * @param index индекс элемента
        * @return константная ссылка на элемент
        */
        const int& operator[](size_t index) const;

        /**
        * @brief Оператор разыменования (возвращает указатель на данные)
        * @return указатель на внутренний массив данных
        */
        const int* operator*() const;
    };
}