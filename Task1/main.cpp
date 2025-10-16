#include <iostream>
#include <memory>
#include <locale>
#include "../decision/Matrix.h"
#include "../decision/RandomGenerator.h"
#include "../decision/IStreamGenerator.h"
#include "../decision/Task1.h"
#include "../decision/Task2.h"
#include "../decision/Task3.h"

using namespace miit::algebra;
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    try
    {
        cout << "=== Демонстрация работы с матрицей ===" << endl;

        // Создаем исходные данные
        vector<int> original_data = { 10, 13, 25, 30, 37 };
        cout << "Исходные данные: [10, 13, 25, 30, 37]" << endl;

        // Задание 1 - создаем КОПИЮ для задания 1
        cout << "\n--- Задание 1 ---" << endl;
        auto task1_matrix = make_unique<Matrix>(original_data); // Копия исходных данных
        cout << "Матрица для задания 1: " << task1_matrix->to_string() << endl;
        auto task1 = make_unique<Task1Exercise>(move(task1_matrix), nullptr);
        task1->Task1();
        cout << "После задания 1: " << task1->get_matrix_string() << endl;

        // Задание 2 - создаем НОВУЮ КОПИЮ для задания 2  
        cout << "\n--- Задание 2 ---" << endl;
        auto task2_matrix = make_unique<Matrix>(original_data); // Новая копия исходных данных
        cout << "Матрица для задания 2: " << task2_matrix->to_string() << endl;
        auto task2 = make_unique<Task2Exercise>(move(task2_matrix), nullptr, 3);
        task2->Task2();
        cout << "После задания 2: " << task2->get_matrix_string() << endl;

        // Задание 3 - создаем ЕЩЕ ОДНУ КОПИЮ для задания 3
        cout << "\n--- Задание 3 ---" << endl;
        auto task3_matrix = make_unique<Matrix>(original_data); // Еще одна копия
        cout << "Матрица для задания 3: " << task3_matrix->to_string() << endl;
        auto task3 = make_unique<Task3Exercise>(move(task3_matrix), nullptr);
        auto result3 = task3->Task3();
        cout << "Результат задания 3: " << result3->to_string() << endl;

        // Демонстрация с разными данными
        cout << "\n=== Дополнительная демонстрация ===" << endl;

        // Демо 1: Случайное заполнение
        cout << "\n1. Случайное заполнение матрицы:" << endl;
        auto random_matrix = make_unique<Matrix>(8);
        random_matrix->fill(make_unique<RandomGenerator>(1, 50));
        cout << "Случайная матрица: " << random_matrix->to_string() << endl;

        // Применяем задание 1 к случайной матрице
        auto random_task1 = make_unique<Task1Exercise>(move(random_matrix), nullptr);
        random_task1->Task1();
        cout << "После задания 1: " << random_task1->get_matrix_string() << endl;

        // Демо 2: Операторы матрицы
        cout << "\n2. Демонстрация операторов матрицы:" << endl;
        Matrix demo_matrix(vector<int>{1, 2, 3});
        cout << "Исходная: " << demo_matrix.to_string() << endl;

        demo_matrix << 0; // Добавляем в начало
        cout << "После << 0: " << demo_matrix.to_string() << endl;

        int extracted;
        demo_matrix >> extracted; // Извлекаем из начала
        cout << "Извлечено: " << extracted << ", осталось: " << demo_matrix.to_string() << endl;

        demo_matrix[0] = 99; // Изменяем по индексу
        cout << "После demo_matrix[0] = 99: " << demo_matrix.to_string() << endl;

        cout << "\nДемонстрация завершена успешно!" << endl;
    }
    catch (const exception& e)
    {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}