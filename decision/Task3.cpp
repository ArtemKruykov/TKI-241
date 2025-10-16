#include "Task3.h"
#include <vector>

namespace miit::algebra
{
    std::unique_ptr<Matrix> Task3Exercise::Task3()
    {
        const auto& p = matrix->get_data();
        std::vector<int> m(p.size(), 0);

        if (p.size() > 2)
        {
            for (size_t i = 1; i < p.size() - 1; i++)
            {
                m[i] = -p[i] * static_cast<int>(i + 1);
            }
        }

        return std::make_unique<Matrix>(m);
    }
}