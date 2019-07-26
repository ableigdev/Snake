#ifndef SNAKE_CONSOLEFRUITIMPL_H
#define SNAKE_CONSOLEFRUITIMPL_H

#include "IFruit.h"

namespace fruit_impl::console_fruit_impl
{
    // Implement the IFruit interface
    // This implementation will be showing a fruit on the game field like a letter 'F'
    class ConsoleFruitImpl : public interfaces::IFruit
    {
    public:
        ConsoleFruitImpl() = default;
        ConsoleFruitImpl(const ConsoleFruitImpl&) = default;
        ConsoleFruitImpl(ConsoleFruitImpl&&) = default;
        ConsoleFruitImpl& operator=(const ConsoleFruitImpl&) = default;
        ConsoleFruitImpl& operator=(ConsoleFruitImpl&&) = default;
        virtual ~ConsoleFruitImpl() override = default;

        virtual void show() override;
    };
}

#endif // SNAKE_CONSOLEFRUITIMPL_H