#ifndef SNAKE_ISNAKEMODEL_H
#define SNAKE_ISNAKEMODEL_H

namespace interfaces
{
    /*
    The interface which represents abstraction above model of the application 
    (matrix which contains all coordinates of the game field).
    Implementation of this interface allows creating different 
    logic adding or removing objects on the game field.
    */
    class ISnakeModel
    {
    public:
        ISnakeModel() = default;
        ISnakeModel(const ISnakeModel&) = default;
        ISnakeModel(ISnakeModel&&) = default;
        ISnakeModel& operator=(const ISnakeModel&) = default;
        ISnakeModel& operator=(ISnakeModel&&) = default;
        virtual ~ISnakeModel() = default;

        virtual void addPoint(size_t x, size_t y, int value) = 0;
        virtual void deletePoint(size_t x, size_t y) = 0;
        virtual int getPoint(size_t x, size_t y) const = 0;
        virtual size_t getValueOfXSize() const = 0;
        virtual size_t getValueOfYSize() const = 0;
    };
}

#endif // SNAKE_ISNAKEMODEL_H