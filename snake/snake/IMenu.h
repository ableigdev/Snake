#ifndef SNAKE_IMENU_H
#define SNAKE_IMENU_H

namespace interfaces
{
    /*
    The interface which represents abstraction above the menu. 
    Implementation of this interface allows create a lot of 
    different menus (GUI or console) and use them in our game. 
    It makes the architecture of the application flexible.
    */
    class IMenu
    {
    public: 
        IMenu() = default;
        IMenu(const IMenu&) = delete;
        IMenu(IMenu&&) = default;
        IMenu& operator=(const IMenu&) = delete;
        IMenu& operator=(IMenu&&) = default;
        virtual ~IMenu() = default;

        virtual void show() = 0;
    };
}

#endif // SNAKE_IMENU_H