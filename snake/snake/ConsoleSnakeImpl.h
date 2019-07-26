#ifndef SNAKE_CONSOLESNAKEIMPL_H
#define SNAKE_CONSOLESNAKEIMPL_H

#include "ISnake.h"

namespace snake_impl::console_snake_impl
{
    // Implement the ISnake interface
    class ConsoleSnakeImpl : public interfaces::ISnake
    {
    public:
        ConsoleSnakeImpl() = default;
        ConsoleSnakeImpl(const ConsoleSnakeImpl&) = default;
        ConsoleSnakeImpl(ConsoleSnakeImpl&&) = default;
        ConsoleSnakeImpl& operator=(const ConsoleSnakeImpl&) = default;
        ConsoleSnakeImpl& operator=(ConsoleSnakeImpl&&) = default;
        virtual ~ConsoleSnakeImpl() override = default;

        // These methods show how to view part of the snake body
        virtual void showHead() override;
        virtual void showBody() override;
        virtual void showTail() override;
    };
}

#endif // SNAKE_CONSOLESNAKEIMPL_H