#ifndef SNAKE_IVIEWER_H
#define SNAKE_IVIEWER_H

#include <Windows.h>
#include <deque>

namespace interfaces
{
    class ISnakeModel;

    /*
    The interface which represents abstraction above the view.
    Implementation of this interface allows show for user all 
    information (score, level) and all game objects (snake, fruits, walls).
    */
    class IViewer
    {
    public:
        IViewer() = default;
        virtual ~IViewer() = default;
        virtual void setSizeOfX(size_t x) = 0;
        virtual void setSizeOfY(size_t y) = 0;
        virtual void resetSnake() = 0;
        virtual std::deque<POINT> getAllSnakeBody() const = 0;
        virtual void setSnakeBody(const std::deque<POINT>& body) = 0;
        virtual void addPointOfBody(const POINT& point) = 0;
        virtual void addPointOfBodyToBegin(const POINT& point) = 0;
        virtual POINT getHeadOfSnake() const = 0;
        virtual POINT getTailOfSnake() const = 0;
        virtual void removeOldTail() = 0;
        virtual void updateScore(size_t score) = 0;
        virtual size_t score() const = 0;
        virtual void updateLevel() = 0;
        virtual void draw(const ISnakeModel& snakeModel) = 0;
        virtual void showData() = 0;
        virtual void delay() = 0;
    };
}

#endif // SNAKE_IVIEWER_H