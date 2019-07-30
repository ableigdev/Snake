#include <utility>
#include <iostream>
#include <memory>
#include <conio.h>
#include <vector>
#include "ConsoleMenuImpl.h"
#include "move_to.h"
#include "constants.h"
#include "ConsoleFactoryImpl.h"
#include "ControllerImpl.h"
#include "SnakeModelImpl.h"
#include "AutoPlayControllerImpl.h"

menu_impl::console_menu_impl::ConsoleMenuImpl::ConsoleMenuImpl()
    : IMenu(),
    m_ConsoleFactory(std::make_unique<factory_impl::console_factory_impl::ConsoleFactoryImpl>()),
    m_Index(1),
    m_Key(0)
{
    m_StdHandle = GetStdHandle(STD_OUTPUT_HANDLE); // Get input console handle
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS); // Ignore mouse click
}

menu_impl::console_menu_impl::ConsoleMenuImpl::ConsoleMenuImpl(ConsoleMenuImpl&& consoleMenu)
    : m_Index(std::move(consoleMenu.m_Index)),
    m_Key(std::move(consoleMenu.m_Key)),
    m_StdHandle(std::move(consoleMenu.m_StdHandle))
{
    consoleMenu.m_Index = 0;
    consoleMenu.m_Key = 0;
    consoleMenu.m_StdHandle = nullptr;
}

menu_impl::console_menu_impl::ConsoleMenuImpl& menu_impl::console_menu_impl::ConsoleMenuImpl::operator=(ConsoleMenuImpl&& rConsoleMenu)
{
    if (this != &rConsoleMenu)
    {
        m_Index = std::move(rConsoleMenu.m_Index);
        m_Key = std::move(rConsoleMenu.m_Key);
        m_StdHandle = std::move(rConsoleMenu.m_StdHandle);
        rConsoleMenu.m_Index = 0;
        rConsoleMenu.m_Key = 0;
        rConsoleMenu.m_StdHandle = nullptr;
    }
    return *this;
}

void menu_impl::console_menu_impl::ConsoleMenuImpl::show()
{
    m_Key = 0;
    system("cls");
    while (m_Key != 13)
    {
        helpers::moveToXY(3, 3);
        changeColor(helpers::Colors::WHITE);
        std::cout << "SNAKE GAME CONSOLE";
       
        helpers::moveToXY(3, 4);
        std::cout << "==================";
        
        helpers::moveToXY(3, 5);
        changeColor(helpers::Colors::WHITE);
        
        if (m_Index == 1) 
        { 
            changeColor(helpers::Colors::LIGHTGREEN);
        }
        
        std::cout << "START";
        helpers::moveToXY(3, 6);
        changeColor(helpers::Colors::WHITE);
        
        if (m_Index == 2)
        { 
            changeColor(helpers::Colors::LIGHTGREEN);
        }
        
        std::cout << "AUTOPLAY";
        helpers::moveToXY(3, 7);
        changeColor(helpers::Colors::WHITE);
        
        if (m_Index == 3)
        { 
            changeColor(helpers::Colors::LIGHTGREEN);
        }

        std::cout << "ABOUT";
        helpers::moveToXY(3, 8);
        changeColor(helpers::Colors::WHITE);
        
        if (m_Index == 4)
        { 
            changeColor(helpers::Colors::LIGHTGREEN);
        }
        
        std::cout << "EXIT";
        
        // UP=72 Down=80 Enter=13
        m_Key = _getch();
        if (m_Key == 80)
        { 
            ++m_Index;
        }
        else if (m_Key == 72)
        { 
            --m_Index;
        }
        
        if (m_Index == 5) 
        { 
            m_Index = 1; 
        }
        
        if (m_Index == 0) 
        { 
            m_Index = 4; 
        }
    }

    if (m_Index == 1) 
    { 
        start(); 
    }
    else if (m_Index == 2)
    {
        autoPlay();
    }
    else if (m_Index == 3)
    {
        showAbout();
    }
    else if (m_Index == 4)
    {
        exit(0);
    }
}

void menu_impl::console_menu_impl::ConsoleMenuImpl::start()
{
    // Initialize all components for the new game
    POINT sizeOfField = chooseSizeOfField();

    auto fruits(m_ConsoleFactory->createFruits());
    auto snake(m_ConsoleFactory->createSnake());
    auto viewer(m_ConsoleFactory->createViewer(std::move(snake), std::move(fruits)));
    auto model(std::make_unique<snake_model_impl::SnakeModelImpl>(sizeOfField.x, sizeOfField.y));
    auto controller(std::make_unique<controller_impl::ControllerImpl>(std::move(viewer), std::move(model)));

    size_t score = controller->play();
    // Transfer the pointer to the function which will execute
    gameOver(score, std::bind(&ConsoleMenuImpl::start, this));
    show();
}

void menu_impl::console_menu_impl::ConsoleMenuImpl::showAbout()
{
    system("cls");
    m_Key = 0;
    
    // Enter=13, Esc=27
    while (m_Key != 13 && m_Key != 27)
    {
        helpers::moveToXY(3, 3); 
        changeColor(helpers::Colors::LIGHTGREEN);
        std::cout << "============================";
        helpers::moveToXY(3, 4);
        std::cout << "|    SNAKE GAME CONSOLE    |";
        helpers::moveToXY(3, 5);
        std::cout << "============================";
        helpers::moveToXY(3, 6); 
        
        changeColor(helpers::Colors::WHITE);
        std::cout << "Created by Ihor Yarovyi.";
        helpers::moveToXY(3, 7);
        std::cout << "Pingle Studio. 2019.";
        m_Key = _getch();
    }
    show();
}

void menu_impl::console_menu_impl::ConsoleMenuImpl::changeColor(int color)
{
    SetConsoleTextAttribute(m_StdHandle, static_cast<WORD>(color));
}

void menu_impl::console_menu_impl::ConsoleMenuImpl::gameOver(size_t score, std::function<void()> startGame)
{
    system("cls");
    m_Key = 0;
    size_t currentIndex = 1;

    while (m_Key != 13)
    {
        helpers::moveToXY(3, 3);
        changeColor(helpers::Colors::LIGHTGREEN);
        std::cout << "GAME OVER!";
        
        helpers::moveToXY(3, 5);
        changeColor(helpers::Colors::WHITE);
        std::cout << "Your score: " << score;
        
        helpers::moveToXY(3, 7);
        std::cout << "Do you want to play again?";

        helpers::moveToXY(3, 9);

        if (currentIndex == 1)
        {
            changeColor(helpers::Colors::LIGHTGREEN);
        }
        std::cout << "YES";
        
        helpers::moveToXY(3, 10);
        changeColor(helpers::Colors::WHITE);

        if (currentIndex == 2)
        {
            changeColor(helpers::Colors::LIGHTGREEN);
        }
        std::cout << "NO";

        m_Key = _getch();

        // UP=72 Down=80 Enter=13
        if (m_Key == 80)
        {
            ++currentIndex;
        }
        else if (m_Key == 72)
        {
            --currentIndex;
        }

        if (currentIndex == 0)
        {
            currentIndex = 2;
        }

        if (currentIndex == 3)
        {
            currentIndex = 1;
        }
    }

    if (currentIndex == 1)
    {
        startGame(); // Start the new game
    }
}

POINT menu_impl::console_menu_impl::ConsoleMenuImpl::chooseSizeOfField()
{
    size_t currentIndex = 1;
    POINT result{ 30, 24 };
    m_Key = 0;
    system("cls");

    while (m_Key != 13)
    {
        helpers::moveToXY(3, 3);
        changeColor(helpers::Colors::WHITE);
        std::cout << "Choose the size of the game field:";

        helpers::moveToXY(3, 4);

        if (currentIndex == 1)
        {
            changeColor(helpers::Colors::LIGHTGREEN);
        }

        std::cout << "30 x 24";

        helpers::moveToXY(3, 5);
        changeColor(helpers::Colors::WHITE);

        if (currentIndex == 2)
        {
            changeColor(helpers::Colors::LIGHTGREEN);
        }

        std::cout << "50 x 30";

        helpers::moveToXY(3, 6);
        changeColor(helpers::Colors::WHITE);

        if (currentIndex == 3)
        {
            changeColor(helpers::Colors::LIGHTGREEN);
        }

        std::cout << "70 x 30";

        m_Key = _getch();

        // UP=72 Down=80 Enter=13
        if (m_Key == 80)
        {
            ++currentIndex;
        }
        else if (m_Key == 72)
        {
            --currentIndex;
        }
        else if (m_Key == 27)
        {
            show();
        }

        if (currentIndex == 0)
        {
            currentIndex = 3;
        }

        if (currentIndex == 4)
        {
            currentIndex = 1;
        }
    }

    if (currentIndex == 1)
    {
        result.x = 30;
        result.y = 24;
    }
    else if (currentIndex == 2)
    {
        result.x = 50;
        result.y = 30;
    }
    else if (currentIndex == 3)
    {
        result.x = 70;
        result.y = 30;
    }

    changeColor(helpers::Colors::WHITE);
    system("cls");
    return result;
}

void menu_impl::console_menu_impl::ConsoleMenuImpl::autoPlay()
{
    // Initialize all components for the new game
    POINT sizeOfField = chooseSizeOfField();

    auto fruits(m_ConsoleFactory->createFruits());
    auto snake(m_ConsoleFactory->createSnake());
    auto viewer(m_ConsoleFactory->createViewer(std::move(snake), std::move(fruits)));
    auto model(std::make_unique<snake_model_impl::SnakeModelImpl>(sizeOfField.x, sizeOfField.y));
    auto controller(std::make_unique<controller_impl::AutoPlayControllerImpl>(std::move(viewer), std::move(model)));

    size_t score = controller->play();
    // Transfer the pointer to the function which will execute
    gameOver(score, std::bind(&ConsoleMenuImpl::autoPlay, this));
    show();
}

