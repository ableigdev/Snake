#include <iostream>
#include "ConsoleViewerImpl.h"
#include "SnakeModelImpl.h"
#include "move_to.h"
#include "constants.h"

viewer_impl::console_viewer_impl::ConsoleViewerImpl::ConsoleViewerImpl(
    std::unique_ptr<interfaces::ISnake>&& snake, 
    std::vector<std::unique_ptr<interfaces::IFruit>>&& fruits)
    : interfaces::IViewer(),
    m_Snake(std::move(snake)),
    m_Fruits(std::move(fruits))
{
    m_SizeGreaterThanOne = m_Fruits.size() > 1; // Set up the flag
}

void viewer_impl::console_viewer_impl::ConsoleViewerImpl::setSizeOfX(size_t x)
{
    m_SizeOfX = x;
}

void viewer_impl::console_viewer_impl::ConsoleViewerImpl::setSizeOfY(size_t y)
{
    m_SizeOfY = y;
}

void viewer_impl::console_viewer_impl::ConsoleViewerImpl::resetSnake()
{
    m_Snake->resetBodyToDefaultState();
}

std::deque<POINT> viewer_impl::console_viewer_impl::ConsoleViewerImpl::getAllSnakeBody() const
{
    return m_Snake->getAllSnakeBody();
}

void viewer_impl::console_viewer_impl::ConsoleViewerImpl::setSnakeBody(const std::deque<POINT>& body)
{
    m_Snake->setSnakeBody(body);
}

void viewer_impl::console_viewer_impl::ConsoleViewerImpl::addPointOfBody(const POINT& point)
{
    m_Snake->addPointOfBody(point);
}

POINT viewer_impl::console_viewer_impl::ConsoleViewerImpl::getHeadOfSnake() const
{
    return m_Snake->getHeadOfSnake();
}

POINT viewer_impl::console_viewer_impl::ConsoleViewerImpl::getTailOfSnake() const
{
    return m_Snake->getTailOfSnake();
}

void viewer_impl::console_viewer_impl::ConsoleViewerImpl::removeOldTail()
{
    m_Snake->removeOldTail();
}

void viewer_impl::console_viewer_impl::ConsoleViewerImpl::draw(const interfaces::ISnakeModel& snakeModel)
{
    // Get size of the game field
    m_SizeOfY = snakeModel.getValueOfYSize();
    m_SizeOfX = snakeModel.getValueOfXSize();

    for (size_t j = 0; j < m_SizeOfY; ++j)
    {
        for (size_t i = 0; i < m_SizeOfX; ++i)
        {
            // Go to (x, y) position
            helpers::moveToXY(static_cast<short>(i), static_cast<short>(j));
            
            // Get the value of the current cell
            // If a value of the current cell equal value of the snake body
            if (int currentValueOfPoint = snakeModel.getPoint(i, j); currentValueOfPoint == helpers::tagsOfTheGameSpace::SNAKE_BODY)
            {
                m_Snake->showBody(); // Show the texture of the snake body
            }// If a value of the current cell equal value of the wall
            else if (currentValueOfPoint == helpers::tagsOfTheGameSpace::WALL)
            {
                std::cout << "8"; // Show the texture of the wall
            } // If a value of the current cell equal value of the fruit
            else if (currentValueOfPoint == helpers::tagsOfTheGameSpace::FRUIT)
            {
                // If the size of the m_Fruits greater than 1,
                // we show 'F' when the level is even and '@' when the level is odd
                // When the size is 1, we show the first fruit which contains in the m_Fruit
                
                // P.S. This is a primitive sample which shows this opportunity. 
                // I can create more beautiful switching between fruits when It necessary.
                size_t index = m_SizeGreaterThanOne ? (m_Level & 1) : 0;
                m_Fruits[index]->show(); // Show the texture of the fruit
            } // If a value of the current cell equal value of the snake's head
            else if (currentValueOfPoint == helpers::tagsOfTheGameSpace::SNAKE_HEAD)
            {
                m_Snake->showHead(); // Show the texture of the snake's head
            } // If a value of the current cell equal value of the snake's tail
            else if (currentValueOfPoint == helpers::tagsOfTheGameSpace::SNAKE_TAIL)
            {
                m_Snake->showTail(); // Show the texture of the snake's tail
            }
            else
            {
                std::cout << " "; // Show the texture of the free space
            }
        }
    }
}

void viewer_impl::console_viewer_impl::ConsoleViewerImpl::showData()
{
    helpers::moveToXY(static_cast<short>(m_SizeOfX + 3), 2);
    std::cout << "          ";
    helpers::moveToXY(static_cast<short>(m_SizeOfX + 3), 3);
    std::cout << "SCORE: " << m_Score;
    helpers::moveToXY(static_cast<short>(m_SizeOfX + 3), 4);
    std::cout << "LEVEL: " << m_Level;
}

void viewer_impl::console_viewer_impl::ConsoleViewerImpl::delay()
{
    m_Delay = 10 - static_cast<int>(2 * m_Level);

    if (m_Delay < 0)
    {
        m_Delay = 0;
    }
    Sleep(m_Delay * 10);
}

void viewer_impl::console_viewer_impl::ConsoleViewerImpl::updateScore(size_t score)
{
    m_Score += score;
}

void viewer_impl::console_viewer_impl::ConsoleViewerImpl::updateLevel()
{
    m_Level = m_Score / 100;
}

void viewer_impl::console_viewer_impl::ConsoleViewerImpl::addPointOfBodyToBegin(const POINT& point)
{
    m_Snake->addPointOfBodyToBegin(point);
}

size_t viewer_impl::console_viewer_impl::ConsoleViewerImpl::score() const
{
    return m_Score;
}