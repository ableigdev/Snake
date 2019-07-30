#ifndef SNAKE_IFACTORY_H
#define SNAKE_IFACTORY_H

#include <memory>
#include <vector>
#include "IFruit.h"
#include "ISnake.h"
#include "IViewer.h"

namespace interfaces
{
    /*
    The interface which represents abstraction above factories.
    Implementation of this interface allows to create objects of 
    ISnake, IFruit and IViewer are easier.
    */
    class IFactory
    {
    public:
        IFactory() = default;
        virtual ~IFactory() = default;

        virtual std::unique_ptr<ISnake> createSnake() = 0;
        virtual std::vector<std::unique_ptr<IFruit>> createFruits() = 0;
        virtual std::unique_ptr<IViewer> createViewer(std::unique_ptr<interfaces::ISnake>&& snake, 
            std::vector<std::unique_ptr<interfaces::IFruit>>&& fruits) = 0;
    };
}

#endif // SNAKE_IFACTORY_H
