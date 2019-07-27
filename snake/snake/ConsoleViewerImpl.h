#ifndef SNAKE_CONSOLEVIEWERIMPL_H
#define SNAKE_CONSOLEVIEWERIMPL_H

#include <memory>
#include <vector>
#include "IViewer.h"
#include "ISnake.h"
#include "IFruit.h"

namespace viewer_impl::console_viewer_impl
{
    // Implement the IViewer interface
    class ConsoleViewerImpl : public interfaces::IViewer
    {
    public:
        ConsoleViewerImpl(std::unique_ptr<interfaces::ISnake>&& snake, std::vector<std::unique_ptr<interfaces::IFruit>>&& fruits);
        virtual ~ConsoleViewerImpl() override = default;
        virtual void setSizeOfX(size_t x) override;
        virtual void setSizeOfY(size_t y) override;
        virtual void resetSnake() override;
        virtual std::deque<POINT> getAllSnakeBody() const override;
        virtual void setSnakeBody(const std::deque<POINT>& body) override;
        virtual void addPointOfBody(const POINT& point) override;
        virtual void addPointOfBodyToBegin(const POINT& point) override;
        virtual POINT getHeadOfSnake() const override;
        virtual POINT getTailOfSnake() const override;
        virtual void removeOldTail() override;
        virtual void updateScore(size_t score) override;
        virtual size_t score() const override;
        virtual void updateLevel() override;
        virtual void draw(const interfaces::ISnakeModel& snakeModel) override;
        virtual void showData() override;
        virtual void delay() override;

    private:
        // The pointer on ISnake interface; It allows to work with different snakes
        // without rewrite code
        std::unique_ptr<interfaces::ISnake> m_Snake; 
        // The array with pointers of IFruit; It allows switch between fruits
        // when they are being shown for user
        std::vector<std::unique_ptr<interfaces::IFruit>> m_Fruits;
        bool m_SizeGreaterThanOne; // The flag which shows that m_Fruits has a size greater than 1
        size_t m_SizeOfX {};
        size_t m_SizeOfY {};
        size_t m_Level {};
        size_t m_Score {};
        int m_Delay {};
    };
}

#endif // SNAKE_CONSOLEVIEWERIMPL_H
