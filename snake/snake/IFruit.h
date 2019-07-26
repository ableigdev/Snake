#ifndef SNAKE_IFRUIT_H
#define SNAKE_IFRUIT_H

namespace interfaces
{
    /*
    The interface which represents abstraction above all fruits. 
    Implementation of this interface allows create a lot of different 
    fruits and use them in our game.  
    */
    class IFruit
    {
    public:
        IFruit() = default;
        IFruit(const IFruit&) = default;
        IFruit(IFruit&&) = default;
        IFruit& operator=(const IFruit&) = default;
        IFruit& operator=(IFruit&&) = default;
        virtual ~IFruit() = default;

        virtual void show() = 0;
    };
}

#endif // SNAKE_IFRUIT_H