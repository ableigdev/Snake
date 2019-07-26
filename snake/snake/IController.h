#ifndef SNAKE_ICONTROLLER_H
#define SNAKE_ICONTROLLER_H

namespace interfaces
{
    /*
    The interface which represents abstraction above controllers. 
    Implementation of this interface allows controlling user interface and model.
    */
    class IController
    {
    public:
        IController() = default;
        virtual ~IController() = default;
        virtual size_t play() = 0;
    };
}

#endif // SNAKE_ICONTROLLER_H