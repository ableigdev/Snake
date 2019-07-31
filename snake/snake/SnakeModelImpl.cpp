#include <algorithm>
#include <stdexcept>
#include "SnakeModelImpl.h"
#include "constants.h"

snake_model_impl::SnakeModelImpl::SnakeModelImpl(size_t x, size_t y)
    : interfaces::ISnakeModel()
{
    m_Matrix.resize(x);

    for (size_t i = 0; i < m_Matrix.size(); ++i)
    {
        m_Matrix[i].resize(y);
    }

    for (size_t i = 0; i < x; ++i)
    {
        for (size_t j = 0; j < y; ++j)
        {
            m_Matrix[i][j] = helpers::tagsOfTheGameSpace::FREE_SPACE; // Free space is being filled
            // The wall is being built
            m_Matrix[0][j] = helpers::tagsOfTheGameSpace::WALL;
            m_Matrix[x - 1][j] = helpers::tagsOfTheGameSpace::WALL;
            m_Matrix[i][0] = helpers::tagsOfTheGameSpace::WALL;
            m_Matrix[i][y - 1] = helpers::tagsOfTheGameSpace::WALL;
        }
    }
}

snake_model_impl::SnakeModelImpl::SnakeModelImpl(const SnakeModelImpl& snakeModel)
    : m_Matrix(snakeModel.m_Matrix)
{

}

snake_model_impl::SnakeModelImpl::SnakeModelImpl(SnakeModelImpl&& snakeModel)
    : m_Matrix(std::move(snakeModel.m_Matrix))
{

}

snake_model_impl::SnakeModelImpl& snake_model_impl::SnakeModelImpl::operator=(const SnakeModelImpl& rSnakeModel)
{
    if (this != &rSnakeModel)
    {
        m_Matrix = rSnakeModel.m_Matrix;
    }
    return *this;
}

snake_model_impl::SnakeModelImpl& snake_model_impl::SnakeModelImpl::operator=(SnakeModelImpl&& rSnakeModel)
{
    if (this != &rSnakeModel)
    {
        m_Matrix = std::move(rSnakeModel.m_Matrix);
    }
    return *this;
}

void snake_model_impl::SnakeModelImpl::addPoint(size_t x, size_t y, int value)
{
    if (checkRange(x, y))
    {
        // If point exists and this point not equal the wall
        if (m_Matrix[x][y] != helpers::tagsOfTheGameSpace::WALL) 
        {
            m_Matrix[x][y] = value; // Add to field
        }
    }
}

void snake_model_impl::SnakeModelImpl::deletePoint(size_t x, size_t y)
{
    if (checkRange(x, y))
    {
        // If point exists and this point not equal the wall
        if (m_Matrix[x][y] != helpers::tagsOfTheGameSpace::WALL)
        {
            m_Matrix[x][y] = 0; // Delete from field
        }
    }
    else
    {
        throw std::out_of_range("Out of range in the 'deletePoint' method");
    }
}

int snake_model_impl::SnakeModelImpl::getPoint(size_t x, size_t y) const
{
    if (checkRange(x, y))
    {
        return m_Matrix[x][y];
    }
    else
    {
        throw std::out_of_range("Out of range in the 'getPoint' method");
    }
}

// Check condition when the coordinate x and y less than the size of the array
bool snake_model_impl::SnakeModelImpl::checkRange(size_t x, size_t y) const
{
    return x < m_Matrix.size() && y < m_Matrix[x].size();
}

size_t snake_model_impl::SnakeModelImpl::getValueOfXSize() const
{
    return m_Matrix.size();
}

size_t snake_model_impl::SnakeModelImpl::getValueOfYSize() const
{
    return m_Matrix.front().size();
}