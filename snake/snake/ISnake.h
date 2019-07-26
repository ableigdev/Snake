#ifndef SNAKE_ISNAKE_H
#define SNAKE_ISNAKE_H

#include <deque>
#include <Windows.h>    

namespace interfaces
{
    /*
    The interface which represents abstraction above the snake. 
    Implementation of this interface allows create a lot of 
    different snakes and use them in our game. 
    The class ISnake contain an array of coordinates of the 
    snake's body and methods which allow add and remove parts 
    of the body.
    */
    class ISnake
    {
    public:
        ISnake() 
        { 
            resetBodyToDefaultState(); 
        }

        ISnake(const ISnake& snake) : m_Body(snake.m_Body) {}
        ISnake(ISnake&& snake) : m_Body(std::move(snake.m_Body)) {}
        
        ISnake& operator=(const ISnake& rSnake)
        {
            if (this != &rSnake)
            {
                m_Body = rSnake.m_Body;
            }
            return *this;
        }

        ISnake& operator=(ISnake&& rSnake)
        {
            if (this != &rSnake)
            {
                m_Body = std::move(rSnake.m_Body);
            }
            return *this;
        }

        void resetBodyToDefaultState()
        {
            m_Body.erase(m_Body.begin(), m_Body.end());
            m_Body.push_back({ 5, 5 });
            m_Body.push_back({ 6, 5 });
            m_Body.push_back({ 7, 5 });
        }

        std::deque<POINT> getAllSnakeBody() const
        {
            return m_Body;
        }

        void setSnakeBody(const std::deque<POINT>& body)
        {
            m_Body = body;
        }

        void addPointOfBody(const POINT& point)
        {
            m_Body.push_back(point);
        }

        void addPointOfBodyToBegin(const POINT& point)
        {
            m_Body.push_front(point);
        }

        POINT getHeadOfSnake() const
        {
            return m_Body.back();
        }
        
        POINT getTailOfSnake() const
        {
            return m_Body.front();
        }

        void removeOldTail()
        {
            m_Body.erase(m_Body.begin());
        }

        virtual ~ISnake() = default;
        virtual void showHead() = 0;
        virtual void showBody() = 0;
        virtual void showTail() = 0;

    private:
        std::deque<POINT> m_Body {};
    };
}

#endif // SNAKE_ISNAKE_H