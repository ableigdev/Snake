#ifndef SNAKE_SNAKEMODELIMPL_H
#define SNAKE_SNAKEMODELIMPL_H

#include <vector>
#include "ISnakeModel.h"

namespace snake_model_impl
{
    // Implement the ISnakeModel interface
    class SnakeModelImpl : public interfaces::ISnakeModel
    {
    public:
        SnakeModelImpl(size_t x, size_t y);
        SnakeModelImpl(const SnakeModelImpl& snakeModel);
        SnakeModelImpl(SnakeModelImpl&& snakeModel);
        SnakeModelImpl& operator=(const SnakeModelImpl& rSnakeModel);
        SnakeModelImpl& operator=(SnakeModelImpl&& rSnakeModel);
        virtual ~SnakeModelImpl() override = default;

        virtual void addPoint(size_t x, size_t y, int val) override;
        virtual void deletePoint(size_t x, size_t y) override;
        virtual int getPoint(size_t x, size_t y) const override;
        virtual size_t getValueOfXSize() const override;
        virtual size_t getValueOfYSize() const override;

    private:
        bool checkRange(size_t x, size_t y) const;

    private:
        std::vector<std::vector<int>> m_Matrix;
    };
}

#endif // !SNAKE_SNAKEMODELIMPL_H
