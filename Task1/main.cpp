#include <iostream>
#include <memory>
#include <locale>
#include <limits>
#include "../decision/Matrix.h"
#include "../decision/RandomGenerator.h"
#include "../decision/IStreamGenerator.h"
#include "../decision/Task1.h"
#include "../decision/Task2.h"
#include "../decision/Task3.h"

using namespace miit::algebra;
using namespace std;

// Enum для выбора способа заполнения матрицы
enum class FillMethod {
    RANDOM = 1,
    KEYBOARD = 2
};

/**
 * @brief Выбор способа заполнения матрицы пользователем
 * @return Выбранный способ заполнения
 */
FillMethod chooseFillMethod();

/**
 * @brief Получение размера матрицы от пользователя
 * @return Размер матрицы
 */
size_t getMatrixSize();

/**
 * @brief Получение диапазона для случайного заполнения
 * @return Пара (min, max) - минимальное и максимальное значение
 */
pair<int, int> getRandomRange();

/**
 * @brief Ввод элементов матрицы с клавиатуры
 * @param size Размер матрицы
 * @return Вектор с введенными элементами
 */
vector<int> inputMatrixFromKeyboard(size_t size);

int main()
{
    setlocale(LC_ALL, "Russian");

    try
    {
        cout << "=== Демонстрация работы с матрицей ===" << endl;

        FillMethod method = chooseFillMethod();

        unique_ptr<Matrix> main_matrix;
        vector<int> original_data;

        switch (method) {
        case FillMethod::RANDOM: {
            size_t size = getMatrixSize();
            auto [min, max] = getRandomRange();

            main_matrix = make_unique<Matrix>(size);
            main_matrix->fill(make_unique<RandomGenerator>(min, max));
            original_data = main_matrix->get_data();

            cout << "\nСоздана матрица размером " << size
                << " со случайными числами от " << min << " до " << max << endl;
            break;
        }

        case FillMethod::KEYBOARD: {
            size_t size = getMatrixSize();
            original_data = inputMatrixFromKeyboard(size);
            main_matrix = make_unique<Matrix>(original_data);
            cout << "\nМатрица успешно введена с клавиатуры." << endl;
            break;
        }
        }

        cout << "Исходная матрица: " << main_matrix->to_string() << endl;

        cout << "\n--- Задание 1 ---" << endl;
        auto task1_matrix = make_unique<Matrix>(original_data);
        cout << "Матрица для задания 1: " << task1_matrix->to_string() << endl;
        auto task1 = make_unique<Task1Exercise>(move(task1_matrix), nullptr);
        task1->Task1();
        cout << "После задания 1: " << task1->get_matrix_string() << endl;

        cout << "\n--- Задание 2 ---" << endl;
        auto task2_matrix = make_unique<Matrix>(original_data);
        cout << "Матрица для задания 2: " << task2_matrix->to_string() << endl;
        auto task2 = make_unique<Task2Exercise>(move(task2_matrix), nullptr, 3);
        task2->Task2();
        cout << "После задания 2: " << task2->get_matrix_string() << endl;

        cout << "\n--- Задание 3 ---" << endl;
        auto task3_matrix = make_unique<Matrix>(original_data);
        cout << "Матрица для задания 3: " << task3_matrix->to_string() << endl;
        auto task3 = make_unique<Task3Exercise>(move(task3_matrix), nullptr);
        auto result3 = task3->Task3();
        cout << "Результат задания 3: " << result3->to_string() << endl;
    }
    catch (const exception& e)
    {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}

FillMethod chooseFillMethod() {
    int choice;
    cout << "\nВыберите способ заполнения матрицы:\n";
    cout << static_cast<int>(FillMethod::RANDOM) << " - Случайное заполнение\n";
    cout << static_cast<int>(FillMethod::KEYBOARD) << " - Ввод с клавиатуры\n";
    cout << "Ваш выбор: ";

    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Ошибка ввода! Введите число " +
            to_string(static_cast<int>(FillMethod::RANDOM)) + " или " +
            to_string(static_cast<int>(FillMethod::KEYBOARD)));
    }

    switch (choice) {
    case static_cast<int>(FillMethod::RANDOM):
        return FillMethod::RANDOM;
    case static_cast<int>(FillMethod::KEYBOARD):
        return FillMethod::KEYBOARD;
    default:
        throw runtime_error("Неверный выбор! Введите " +
            to_string(static_cast<int>(FillMethod::RANDOM)) + " или " +
            to_string(static_cast<int>(FillMethod::KEYBOARD)));
    }
}


size_t getMatrixSize() {
    int size;
    cout << "Введите размер матрицы: ";
    cin >> size;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Ошибка! Введите целое число для размера матрицы.");
    }

    if (size <= 0) {
        throw runtime_error("Размер матрицы должен быть положительным числом!");
    }

    return static_cast<size_t>(size);
}


pair<int, int> getRandomRange() {
    int min, max;

    cout << "Введите минимальное значение: ";
    cin >> min;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Ошибка! Введите целое число для минимального значения.");
    }

    cout << "Введите максимальное значение: ";
    cin >> max;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Ошибка! Введите целое число для максимального значения.");
    }

    if (max < min) {
        throw runtime_error("Максимальное значение не может быть меньше минимального!");
    }

    return { min, max };
}

vector<int> inputMatrixFromKeyboard(size_t size) {
    vector<int> matrix_data;
    matrix_data.reserve(size);

    cout << "Введите " << size << " элементов матрицы:" << endl;
    for (size_t i = 0; i < size; i++) {
        int value;
        cout << "Элемент " << (i + 1) << ": ";
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Ошибка! Введите целое число для элемента " + to_string(i + 1));
        }

        matrix_data.push_back(value);
    }

    return matrix_data;
}