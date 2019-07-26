#include <iostream>
#include "ConsoleSnakeImpl.h"

void snake_impl::console_snake_impl::ConsoleSnakeImpl::showHead()
{
    std::cout << "H";
}

void snake_impl::console_snake_impl::ConsoleSnakeImpl::showBody()
{
    std::cout << "0";
}

void snake_impl::console_snake_impl::ConsoleSnakeImpl::showTail()
{
    std::cout << "E";
}