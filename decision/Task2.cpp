#include "Task2.h"
#include <vector>
#include <cmath> // для std::abs

namespace miit::algebra
{
    Task2Exercise::Task2Exercise(std::unique_ptr<Matrix> matrix, std::unique_ptr<Generator> generator, int k)
        : Exercise(std::move(matrix), std::move(generator))
        , k(k)
    {
    }

    void Task2Exercise::Task2()
    {
        std::vector<int> result;
        const auto& data = matrix->get_data();

        for (size_t i = 0; i < data.size(); i++)
        {
            result.push_back(data[i]);

            if (data[i] % 2 != 0) 
            {
                
                int num = std::abs(data[i]); 
                bool contains_k = false;

                // Обрабатываем случай, когда число равно 0 и k тоже 0
                if (num == 0 && k == 0)
                {
                    contains_k = true;
                }
                else
                {
                    while (num > 0)
                    {
                        int digit = num % 10; 
                        if (digit == std::abs(k)) 
                        {
                            contains_k = true;
                            break;
                        }
                        num /= 10; 
                    }
                }

                if (contains_k)
                {
                    result.push_back(k);
                }
            }
        }
        *matrix = Matrix(result);
    }
}