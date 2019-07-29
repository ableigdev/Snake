#ifndef SNAKE_CONSOLEMENUIMPL_H
#define SNAKE_CONSOLEMENUIMPL_H

#include <Windows.h>
#include <functional>
#include "IMenu.h"

namespace menu_impl::console_menu_impl
{
    // Implement the IMenu interface
    class ConsoleMenuImpl : public interfaces::IMenu
    {
    public:
        ConsoleMenuImpl();
        ConsoleMenuImpl(const ConsoleMenuImpl&) = delete;
        ConsoleMenuImpl(ConsoleMenuImpl&& consoleMenu);
        ConsoleMenuImpl& operator=(const ConsoleMenuImpl&) = delete;
        ConsoleMenuImpl& operator=(ConsoleMenuImpl&& rConsoleMenu);
        virtual ~ConsoleMenuImpl() override = default;

        virtual void show() override;

    private:
        void start();
        void autoPlay();
        void showAbout();
        void changeColor(int color);
        void gameOver(size_t score, std::function<void()> startGame);
        POINT chooseSizeOfField();

    private:
        int m_Index;
        int m_Key;
        HANDLE m_StdHandle;
    };
}

#endif // SNAKE_CONSOLEMENUIMPL_H
