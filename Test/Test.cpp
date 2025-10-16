#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <random>
#include <iostream>
#include <cmath>
#include "CppUnitTest.h"
#include "../decision/Matrix.h"
#include "../decision/RandomGenerator.h"
#include "../decision/IStreamGenerator.h"
#include "../decision/Task1.h"
#include "../decision/Task2.h"
#include "../decision/Task3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTests
{
    TEST_CLASS(MatrixTests)
    {
    public:

        TEST_METHOD(MatrixConstructor_ValidSize)
        {
            // Создаем матрицу размером 5
            miit::algebra::Matrix matrix(5);
            // Проверяем, что размер установлен правильно
            Assert::IsTrue(matrix.size() == 5);
        }

        TEST_METHOD(MatrixConstructor_FromVector)
        {
            // Создаем вектор с тестовыми данными
            std::vector<int> data = { 1, 2, 3, 4, 5 };
            // Создаем матрицу из вектора
            miit::algebra::Matrix matrix(data);
            // Проверяем размер и содержимое
            Assert::IsTrue(matrix.size() == data.size());
            Assert::IsTrue(matrix[2] == 3);
        }

        TEST_METHOD(MatrixToString_ValidFormat)
        {
            // Создаем матрицу из вектора
            miit::algebra::Matrix matrix(std::vector<int>{1, 2, 3});
            // Проверяем строковое представление
            std::string result = matrix.to_string();
            std::string expected = "[1, 2, 3]";
            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(MatrixToString_EmptyMatrix)
        {
            // Создаем пустую матрицу
            miit::algebra::Matrix matrix(0);
            // Проверяем строковое представление пустой матрицы
            std::string result = matrix.to_string();
            std::string expected = "[]";
            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(MatrixIndexOperator_ValidAccess)
        {
            // Создаем матрицу с тестовыми данными
            miit::algebra::Matrix matrix(std::vector<int>{10, 20, 30});
            // Проверяем доступ к элементам
            Assert::IsTrue(matrix[1] == 20);
            // Проверяем изменение элемента
            matrix[1] = 25;
            Assert::IsTrue(matrix[1] == 25);
        }

        TEST_METHOD(MatrixIndexOperator_ConstAccess)
        {
            // Создаем константную матрицу
            const miit::algebra::Matrix matrix(std::vector<int>{10, 20, 30});
            // Проверяем доступ к элементам (только чтение)
            Assert::IsTrue(matrix[1] == 20);
        }

        TEST_METHOD(MatrixShiftLeftOperator_ValidBehavior)
        {
            // Создаем матрицу
            miit::algebra::Matrix matrix(std::vector<int>{1, 2, 3});
            // Добавляем элемент в начало
            matrix << 0;
            // Проверяем размер и содержимое
            Assert::IsTrue(matrix.size() == 4);
            Assert::IsTrue(matrix[0] == 0);
            Assert::IsTrue(matrix[1] == 1);
        }

        TEST_METHOD(MatrixShiftRightOperator_ValidBehavior)
        {
            // Создаем матрицу
            miit::algebra::Matrix matrix(std::vector<int>{1, 2, 3});
            int value;
            // Извлекаем элемент из начала
            matrix >> value;
            // Проверяем извлеченное значение и оставшийся размер
            Assert::IsTrue(value == 1);
            Assert::IsTrue(matrix.size() == 2);
            Assert::IsTrue(matrix[0] == 2);
        }

        TEST_METHOD(MatrixDereferenceOperator_ValidPointer)
        {
            // Создаем матрицу
            miit::algebra::Matrix matrix(std::vector<int>{10, 20, 30});
            // Получаем указатель на данные
            const int* data = *matrix;
            // Проверяем данные через указатель
            Assert::IsTrue(data[0] == 10);
            Assert::IsTrue(data[1] == 20);
            Assert::IsTrue(data[2] == 30);
        }

        TEST_METHOD(MatrixAssignmentOperator_ValidCopy)
        {
            // Создаем исходную матрицу
            miit::algebra::Matrix matrix1(std::vector<int>{1, 2, 3});
            // Копируем матрицу
            miit::algebra::Matrix matrix2 = matrix1;
            // Проверяем, что копия идентична оригиналу
            Assert::IsTrue(matrix1.size() == matrix2.size());
            Assert::IsTrue(matrix1[0] == matrix2[0]);
            Assert::IsTrue(matrix1[1] == matrix2[1]);
            Assert::IsTrue(matrix1[2] == matrix2[2]);
        }

        TEST_METHOD(MatrixMoveConstructor_ValidMove)
        {
            // Создаем исходную матрицу
            miit::algebra::Matrix matrix1(std::vector<int>{1, 2, 3});
            // Перемещаем матрицу
            miit::algebra::Matrix matrix2 = std::move(matrix1);
            // Проверяем, что данные переместились
            Assert::IsTrue(matrix2.size() == 3);
            Assert::IsTrue(matrix2[0] == 1);
            Assert::IsTrue(matrix2[1] == 2);
            Assert::IsTrue(matrix2[2] == 3);
        }

        TEST_METHOD(MatrixFill_RandomGenerator)
        {
            // Создаем матрицу
            miit::algebra::Matrix matrix(5);
            // Заполняем случайными числами
            auto generator = std::make_unique<miit::algebra::RandomGenerator>(1, 10);
            matrix.fill(std::move(generator));

            // Проверяем, что все элементы в диапазоне [1, 10]
            for (size_t i = 0; i < matrix.size(); i++) {
                Assert::IsTrue(matrix[i] >= 1 && matrix[i] <= 10);
            }
        }

        TEST_METHOD(MatrixGetData_ValidReference)
        {
            // Создаем исходный вектор
            std::vector<int> original = { 1, 2, 3 };
            // Создаем матрицу из вектора
            miit::algebra::Matrix matrix(original);
            // Получаем ссылку на данные
            const std::vector<int>& data = matrix.get_data();
            // Проверяем размер и содержимое
            Assert::IsTrue(original.size() == data.size());
            Assert::IsTrue(original[1] == data[1]);
        }
    };

    TEST_CLASS(GeneratorTests)
    {
    public:

        TEST_METHOD(RandomGenerator_ValidRange)
        {
            // Создаем генератор с диапазоном [5, 15]
            miit::algebra::RandomGenerator generator(5, 15);
            // Генерируем 100 чисел и проверяем диапазон
            for (int i = 0; i < 100; i++) {
                int value = generator.generate();
                Assert::IsTrue(value >= 5 && value <= 15);
            }
        }

        TEST_METHOD(RandomGenerator_SingleValueRange)
        {
            // Создаем генератор с одним значением
            miit::algebra::RandomGenerator generator(7, 7);
            // Проверяем, что всегда возвращается 7
            Assert::IsTrue(generator.generate() == 7);
            Assert::IsTrue(generator.generate() == 7);
        }

        TEST_METHOD(IStreamGenerator_MockInput)
        {
            // Создаем строковый поток с тестовыми данными
            std::istringstream input("10 20 30 40 50");
            // Создаем генератор из потока
            miit::algebra::IStreamGenerator generator(input);

            // Проверяем чтение данных из потока
            Assert::IsTrue(generator.generate() == 10);
            Assert::IsTrue(generator.generate() == 20);
            Assert::IsTrue(generator.generate() == 30);
        }

        TEST_METHOD(IStreamGenerator_DefaultCin)
        {
            // Создаем генератор с cin по умолчанию
            miit::algebra::IStreamGenerator generator;
            // Просто проверяем, что объект создается без ошибок
            Assert::IsTrue(true);
        }
    };

    TEST_CLASS(Task1Tests)
    {
    public:

        TEST_METHOD(Task1_FirstDivisibleBy5Replaced)
        {
            // Создаем матрицу с числами, кратными 5
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 10, 15, 20});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            // Выполняем задание 1
            task->Task1();
            auto data = task->get_data();

            // Проверяем, что первый элемент кратный 5 (10) заменен на 0
            Assert::IsTrue(data[1] == 0); // 10 должно стать 0
            Assert::IsTrue(data[2] == 15); // 15 остается неизменным
        }

        TEST_METHOD(Task1_NoDivisibleBy5_NoChanges)
        {
            // Создаем матрицу без чисел, кратных 5
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2, 3, 4});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            // Выполняем задание 1
            task->Task1();
            auto data = task->get_data();

            // Проверяем, что массив не изменился
            Assert::IsTrue(data[0] == 1);
            Assert::IsTrue(data[1] == 2);
            Assert::IsTrue(data[2] == 3);
            Assert::IsTrue(data[3] == 4);
        }

        TEST_METHOD(Task1_SingleDivisibleElement)
        {
            // Создаем матрицу с одним элементом, кратным 5
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{25});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            // Выполняем задание 1
            task->Task1();
            auto data = task->get_data();

            // Проверяем, что элемент заменен на 0
            Assert::IsTrue(data[0] == 0);
        }

        TEST_METHOD(Task1_FirstElementDivisible)
        {
            // Создаем матрицу, где первый элемент кратен 5
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{5, 10, 15});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            // Выполняем задание 1
            task->Task1();
            auto data = task->get_data();

            // Проверяем, что первый элемент заменен, остальные не тронуты
            Assert::IsTrue(data[0] == 0); // Первый элемент заменен
            Assert::IsTrue(data[1] == 10); // Остальные не тронуты
            Assert::IsTrue(data[2] == 15);
        }

        TEST_METHOD(Task1_LastElementDivisible)
        {
            // Создаем матрицу, где последний элемент кратен 5
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2, 3, 20});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            // Выполняем задание 1
            task->Task1();
            auto data = task->get_data();

            // Проверяем, что последний элемент заменен, первые остаются
            Assert::IsTrue(data[3] == 0); // Последний элемент заменен
            Assert::IsTrue(data[0] == 1); // Первые остаются
            Assert::IsTrue(data[1] == 2);
            Assert::IsTrue(data[2] == 3);
        }

        TEST_METHOD(Task1_NegativeDivisibleBy5)
        {
            // Создаем матрицу с отрицательными числами, кратными 5
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{-10, -15, -20});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            // Выполняем задание 1
            task->Task1();
            auto data = task->get_data();

            // Проверяем, что первый отрицательный элемент кратный 5 заменен
            Assert::IsTrue(data[0] == 0); // -10 заменен на 0
            Assert::IsTrue(data[1] == -15); // Остальные не тронуты
        }
    };

    TEST_CLASS(Task2Tests)
    {
    public:

        TEST_METHOD(Task2_InsertKAfterOddWithDigitK)
        {
            // Создаем матрицу с нечетными числами, содержащими цифру 3
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{13, 25, 37});
            auto task = std::make_unique<miit::algebra::Task2Exercise>(
                std::move(matrix), nullptr, 3);

            // Выполняем задание 2
            task->Task2();
            auto data = task->get_data();

            // Проверяем вставки числа 3
            Assert::IsTrue(data.size() == 5);
            Assert::IsTrue(data[0] == 13); // 13 содержит 3
            Assert::IsTrue(data[1] == 3);  // вставлена 3 после 13
            Assert::IsTrue(data[2] == 25); // 25 не содержит 3 - без вставки
            Assert::IsTrue(data[3] == 37); // 37 содержит 3
            Assert::IsTrue(data[4] == 3);  // вставлена 3 после 37
        }

        TEST_METHOD(Task2_NoMatchingElements_NoChanges)
        {
            // Создаем матрицу без подходящих элементов
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{12, 24, 36});
            size_t original_size = matrix->size();
            auto task = std::make_unique<miit::algebra::Task2Exercise>(
                std::move(matrix), nullptr, 5);

            // Выполняем задание 2
            task->Task2();

            // Проверяем, что размер не изменился
            Assert::IsTrue(task->size() == original_size);
        }

        TEST_METHOD(Task2_EvenNumbers_NoInsertion)
        {
            // Создаем матрицу только с четными числами
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{12, 24, 36});
            size_t original_size = matrix->size();
            auto task = std::make_unique<miit::algebra::Task2Exercise>(
                std::move(matrix), nullptr, 2);

            // Выполняем задание 2
            task->Task2();

            // Проверяем, что размер не изменился (четные числа не обрабатываются)
            Assert::IsTrue(task->size() == original_size);
        }

        TEST_METHOD(Task2_SingleMatchingElement)
        {
            // Создаем матрицу с одним подходящим элементом
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{13});
            auto task = std::make_unique<miit::algebra::Task2Exercise>(
                std::move(matrix), nullptr, 3);

            // Выполняем задание 2
            task->Task2();
            auto data = task->get_data();

            // Проверяем вставку после одного элемента
            Assert::IsTrue(data.size() == 2);
            Assert::IsTrue(data[0] == 13);
            Assert::IsTrue(data[1] == 3);
        }

        TEST_METHOD(Task2_NumberWithDigitInTensPlace)
        {
            // Создаем матрицу с числами, содержащими цифру 3 в разных позициях
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{31, 42, 53});
            auto task = std::make_unique<miit::algebra::Task2Exercise>(
                std::move(matrix), nullptr, 3);

            // Выполняем задание 2
            task->Task2();
            auto data = task->get_data();

            // Проверяем вставки: 31 содержит 3 в десятках, 53 содержит 3 в единицах
            Assert::IsTrue(data.size() == 5);
            Assert::IsTrue(data[0] == 31);
            Assert::IsTrue(data[1] == 3);  // вставка после 31
            Assert::IsTrue(data[2] == 42); // 42 не содержит 3 - без вставки
            Assert::IsTrue(data[3] == 53);
            Assert::IsTrue(data[4] == 3);  // вставка после 53
        }

        TEST_METHOD(Task2_NegativeNumbersWithDigit)
        {
            // Создаем матрицу с отрицательными числами, содержащими цифру
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{-13, -35, -42});
            auto task = std::make_unique<miit::algebra::Task2Exercise>(
                std::move(matrix), nullptr, 3);

            // Выполняем задание 2
            task->Task2();
            auto data = task->get_data();

            // Проверяем обработку отрицательных чисел
            Assert::IsTrue(data.size() == 5);
            Assert::IsTrue(data[0] == -13); // -13 содержит 3
            Assert::IsTrue(data[1] == 3);   // вставка после -13
            Assert::IsTrue(data[2] == -35); // -35 содержит 3
            Assert::IsTrue(data[3] == 3);   // вставка после -35
            Assert::IsTrue(data[4] == -42); // -42 не содержит 3
        }
    };

    TEST_CLASS(Task3Tests)
    {
    public:

        TEST_METHOD(Task3_CreateModifiedMatrix)
        {
            // Создаем матрицу для задания 3
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2, 3, 4, 5});
            auto task = std::make_unique<miit::algebra::Task3Exercise>(
                std::move(matrix), nullptr);

            // Выполняем задание 3
            auto result = task->Task3();
            auto result_data = result->get_data();

            // Проверяем результат преобразования
            Assert::IsTrue(result->size() == 5);
            Assert::IsTrue(result_data[0] == 0);   // Первый элемент 0
            Assert::IsTrue(result_data[1] == -4);  // -2 * 2
            Assert::IsTrue(result_data[2] == -9);  // -3 * 3
            Assert::IsTrue(result_data[3] == -16); // -4 * 4
            Assert::IsTrue(result_data[4] == 0);   // Последний элемент 0
        }

        TEST_METHOD(Task3_EmptyMatrix)
        {
            // Создаем пустую матрицу
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{});
            auto task = std::make_unique<miit::algebra::Task3Exercise>(
                std::move(matrix), nullptr);

            // Выполняем задание 3
            auto result = task->Task3();

            // Проверяем, что результат тоже пустой
            Assert::IsTrue(result->size() == 0);
        }

        TEST_METHOD(Task3_SingleElement)
        {
            // Создаем матрицу с одним элементом
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{10});
            auto task = std::make_unique<miit::algebra::Task3Exercise>(
                std::move(matrix), nullptr);

            // Выполняем задание 3
            auto result = task->Task3();
            auto result_data = result->get_data();

            // Проверяем результат для одного элемента
            Assert::IsTrue(result->size() == 1);
            Assert::IsTrue(result_data[0] == 0); // Единственный элемент становится 0
        }

        TEST_METHOD(Task3_TwoElements)
        {
            // Создаем матрицу с двумя элементами
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2});
            auto task = std::make_unique<miit::algebra::Task3Exercise>(
                std::move(matrix), nullptr);

            // Выполняем задание 3
            auto result = task->Task3();
            auto result_data = result->get_data();

            // Проверяем результат для двух элементов
            Assert::IsTrue(result->size() == 2);
            Assert::IsTrue(result_data[0] == 0); // Первый элемент 0
            Assert::IsTrue(result_data[1] == 0); // Последний элемент 0
        }

        TEST_METHOD(Task3_ThreeElements)
        {
            // Создаем матрицу с тремя элементами
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2, 3});
            auto task = std::make_unique<miit::algebra::Task3Exercise>(
                std::move(matrix), nullptr);

            // Выполняем задание 3
            auto result = task->Task3();
            auto result_data = result->get_data();

            // Проверяем результат для трех элементов
            Assert::IsTrue(result->size() == 3);
            Assert::IsTrue(result_data[0] == 0);   // Первый элемент 0
            Assert::IsTrue(result_data[1] == -4);  // -2 * 2
            Assert::IsTrue(result_data[2] == 0);   // Последний элемент 0
        }

        TEST_METHOD(Task3_NegativeNumbers)
        {
            // Создаем матрицу с отрицательными числами
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{-1, -2, -3, -4});
            auto task = std::make_unique<miit::algebra::Task3Exercise>(
                std::move(matrix), nullptr);

            // Выполняем задание 3
            auto result = task->Task3();
            auto result_data = result->get_data();

            // Проверяем результат для отрицательных чисел
            Assert::IsTrue(result->size() == 4);
            Assert::IsTrue(result_data[0] == 0);   // Первый элемент 0
            Assert::IsTrue(result_data[1] == 4);   // -(-2) * 2 = 4
            Assert::IsTrue(result_data[2] == 9);   // -(-3) * 3 = 9
            Assert::IsTrue(result_data[3] == 0);   // Последний элемент 0
        }
    };

    TEST_CLASS(ExerciseTests)
    {
    public:

        TEST_METHOD(Exercise_GetMatrixString)
        {
            // Создаем матрицу и упражнение
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2, 3});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            // Получаем строковое представление
            std::string result = task->get_matrix_string();
            std::string expected = "[1, 2, 3]";

            // Проверяем корректность строки
            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(Exercise_MatrixAccess)
        {
            // Создаем матрицу и упражнение
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{10, 20, 30});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            // Получаем доступ к данным через get_data()
            auto data = task->get_data();

            // Проверяем доступ к элементам
            Assert::IsTrue(data[1] == 20);
        }

        TEST_METHOD(Exercise_Size)
        {
            // Создаем матрицу и упражнение
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2, 3, 4, 5});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            // Проверяем размер матрицы
            Assert::IsTrue(task->size() == 5);
        }
    };

    TEST_CLASS(IntegrationTests)
    {
    public:

        TEST_METHOD(FullWorkflow_AllTasks)
        {
            // Создаем исходные данные
            auto original_data = std::vector<int>{ 10, 13, 25, 30, 37 };

            // Задание 1 - создаем отдельную копию
            auto task1_matrix = std::make_unique<miit::algebra::Matrix>(original_data);
            auto task1 = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(task1_matrix), nullptr);
            task1->Task1();
            auto task1_data = task1->get_data();
            Assert::IsTrue(task1_data[0] == 0); // 10 заменен на 0

            // Задание 2 - создаем отдельную копию
            auto task2_matrix = std::make_unique<miit::algebra::Matrix>(original_data);
            auto task2 = std::make_unique<miit::algebra::Task2Exercise>(
                std::move(task2_matrix), nullptr, 3);
            task2->Task2();
            Assert::IsTrue(task2->size() > original_data.size()); // Размер увеличился

            // Задание 3 - создаем отдельную копию
            auto task3_matrix = std::make_unique<miit::algebra::Matrix>(original_data);
            auto task3 = std::make_unique<miit::algebra::Task3Exercise>(
                std::move(task3_matrix), nullptr);
            auto result3 = task3->Task3();
            Assert::IsTrue(result3->size() == original_data.size());

            // Проверяем, что исходные данные не изменились
            auto check_original = miit::algebra::Matrix(original_data);
            auto check_data = check_original.get_data();
            Assert::IsTrue(check_data[0] == 10); // Исходные данные остались неизменными
            Assert::IsTrue(check_data[1] == 13);
            Assert::IsTrue(check_data[2] == 25);
            Assert::IsTrue(check_data[3] == 30);
            Assert::IsTrue(check_data[4] == 37);
        }

        TEST_METHOD(MatrixWithGeneratorIntegration)
        {
            // Создаем матрицу и заполняем через генератор
            auto matrix = std::make_unique<miit::algebra::Matrix>(5);
            auto generator = std::make_unique<miit::algebra::RandomGenerator>(1, 100);
            matrix->fill(std::move(generator));

            // Проверяем размер заполненной матрицы
            Assert::IsTrue(matrix->size() == 5);

            // Применяем задание 1
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);
            task->Task1();

            // Проверяем, что матрица осталась корректного размера
            Assert::IsTrue(task->size() == 5);
        }

        TEST_METHOD(MultipleGeneratorsIntegration)
        {
            // Тестируем работу с разными генераторами
            std::istringstream input("5 10 15 20 25");
            auto stream_generator = std::make_unique<miit::algebra::IStreamGenerator>(input);

            auto matrix = std::make_unique<miit::algebra::Matrix>(5);
            matrix->fill(std::move(stream_generator));

            Assert::IsTrue(matrix->size() == 5);
            Assert::IsTrue((*matrix)[0] == 5);
            Assert::IsTrue((*matrix)[4] == 25);
        }
    };
}