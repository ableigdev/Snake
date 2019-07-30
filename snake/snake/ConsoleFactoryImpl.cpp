#include "ConsoleFactoryImpl.h"
#include "ConsoleFruitImpl.h"
#include "ConsoleSnakeImpl.h"
#include "ConsoleViewerImpl.h"
#include "SecondConsoleFruitImpl.h"

std::unique_ptr<interfaces::ISnake> factory_impl::console_factory_impl::ConsoleFactoryImpl::createSnake()
{
    return std::make_unique<snake_impl::console_snake_impl::ConsoleSnakeImpl>();
}

std::vector<std::unique_ptr<interfaces::IFruit>> factory_impl::console_factory_impl::ConsoleFactoryImpl::createFruits()
{
    auto fruit(std::make_unique<fruit_impl::console_fruit_impl::ConsoleFruitImpl>());
    auto secondFruit(std::make_unique<fruit_impl::console_fruit_impl::SecondConsoleFruitImpl>());
    std::vector <std::unique_ptr<interfaces::IFruit>> fruits;
    fruits.push_back(std::move(fruit));
    fruits.push_back(std::move(secondFruit));

    return fruits;
}

std::unique_ptr<interfaces::IViewer> 
factory_impl::console_factory_impl::ConsoleFactoryImpl::createViewer(std::unique_ptr<interfaces::ISnake>&& snake,
    std::vector<std::unique_ptr<interfaces::IFruit>>&& fruits)
{
    return std::make_unique<viewer_impl::console_viewer_impl::ConsoleViewerImpl>(std::move(snake), std::move(fruits));
}
