#include "Task1.h"

namespace miit::algebra
{
    void Task1Exercise::Task1()
    {
        for (size_t i = 0; i < matrix->size(); i++)
        {
            if ((*matrix)[i] % 5 == 0)
            {
                (*matrix)[i] = 0;
                break;
            }
        }
    }
}