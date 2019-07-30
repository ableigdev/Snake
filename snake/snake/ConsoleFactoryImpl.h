#ifndef SNAKE_CONSOLEFACTORYIMPL_H
#define SNAKE_CONSOLEFACTORYIMPL_H

#include "IFactory.h"

namespace factory_impl::console_factory_impl
{
    // Implement the IFactory interface
    // This class creates the console type of objects
    class ConsoleFactoryImpl : public interfaces::IFactory
    {
    public:
        ConsoleFactoryImpl() = default;
        virtual ~ConsoleFactoryImpl() override = default;

        virtual std::unique_ptr<interfaces::ISnake> createSnake() override;
        virtual std::vector<std::unique_ptr<interfaces::IFruit>> createFruits() override;
        virtual std::unique_ptr<interfaces::IViewer> createViewer(std::unique_ptr<interfaces::ISnake>&& snake,
            std::vector<std::unique_ptr<interfaces::IFruit>>&& fruits) override;
    };
}

#endif // SNAKE_CONSOLEFACTORYIMPL_H
