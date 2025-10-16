#include "Exercise.h"

namespace miit::algebra
{
    Exercise::Exercise(std::unique_ptr<Matrix> matrix, std::unique_ptr<Generator> generator)
        : matrix(std::move(matrix)), generator(std::move(generator))
    {
    }

    std::string Exercise::get_matrix_string() const
    {
        return matrix->to_string();
    }

    const std::vector<int>& Exercise::get_data() const
    {
        return matrix->get_data();
    }

    size_t Exercise::size() const
    {
        return matrix->size();
    }
}