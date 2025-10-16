#include "Matrix.h"
#include <sstream>

namespace miit::algebra
{
    Matrix::Matrix(size_t size) : data(size) {}

    Matrix::Matrix(const std::vector<int>& elements) : data(elements) {}

    void Matrix::fill(std::unique_ptr<Generator> generator)
    {
        for (size_t i = 0; i < data.size(); i++)
        {
            data[i] = generator->generate();
        }
    }

    std::string Matrix::to_string() const
    {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < data.size(); i++)
        {
            oss << data[i];
            if (i < data.size() - 1)
            {
                oss << ", ";
            }
        }
        oss << "]";
        return oss.str();
    }

    size_t Matrix::size() const
    {
        return data.size();
    }

    const std::vector<int>& Matrix::get_data() const
    {
        return data;
    }

    Matrix& Matrix::operator<<(int value)
    {
        data.insert(data.begin(), value);
        return *this;
    }

    Matrix& Matrix::operator>>(int& value)
    {
        if (!data.empty())
        {
            value = data.front();
            data.erase(data.begin());
        }
        return *this;
    }

    int& Matrix::operator[](size_t index)
    {
        return data[index];
    }

    const int& Matrix::operator[](size_t index) const
    {
        return data[index];
    }

    const int* Matrix::operator*() const
    {
        return data.data();
    }
}