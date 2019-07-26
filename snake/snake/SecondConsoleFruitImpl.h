#ifndef SNAKE_SECONDCONSOLEFRUITIMPL_H
#define SNAKE_SECONDCONSOLEFRUITIMPL_H

#include "IFruit.h"

namespace fruit_impl::console_fruit_impl
{
    // The second implementation of the IFruit interface
    // This implementation will be showing a fruit on the game field as a symbol '@'
    class SecondConsoleFruitImpl : public interfaces::IFruit
    {
    public:
        SecondConsoleFruitImpl() = default;
        SecondConsoleFruitImpl(const SecondConsoleFruitImpl&) = default;
        SecondConsoleFruitImpl(SecondConsoleFruitImpl&&) = default;
        SecondConsoleFruitImpl& operator=(const SecondConsoleFruitImpl&) = default;
        SecondConsoleFruitImpl& operator=(SecondConsoleFruitImpl&&) = default;
        virtual ~SecondConsoleFruitImpl() override = default;

        virtual void show() override;
    };
}

#endif // SNAKE_SECONDCONSOLEFRUITIMPL_H
