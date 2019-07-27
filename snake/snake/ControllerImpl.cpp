#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include "ControllerImpl.h"
#include "SnakeModelImpl.h"
#include "constants.h"
#include "ThreadWrapper.h"

controller_impl::ControllerImpl::ControllerImpl(std::unique_ptr<interfaces::IViewer>&& viewer, std::unique_ptr<interfaces::ISnakeModel>&& model)
    : interfaces::IController(),
    m_Viewer(std::move(viewer)),
    m_SnakeModel(std::move(model))
{

}

size_t controller_impl::ControllerImpl::play()
{
    m_OnPlay = true;
    initStartPositionOfFruit();
    initStartPositionOfSnake();
   
    // Execute the function which catches user input in the new thread
    helpers::ThreadWrapper wrapper(std::thread(&ControllerImpl::catchUserInput, this));

    while (m_OnPlay)
    {
        checkWall();
        checkTail();
        moveSnake();
        checkFruit();
        m_Viewer->draw(*m_SnakeModel);
        m_Viewer->showData();
        m_Viewer->delay();
    }

    return m_Viewer->score();
}

void controller_impl::ControllerImpl::catchUserInput()
{
    int k[9] = { 27, 37, 38, 39, 40 };
    int i = 0;
    
    while (m_OnPlay)
    {
        for (int n = 0; n < 5; n++)
        {
            i = k[n];
            // If the key was pressed
            if (GetAsyncKeyState(i) == -32767)
            {
                // Determine which key was pressed and set direction
                if (i == 37)
                {
                    m_Direction = helpers::Direction::LEFT;
                }
                else if (i == 39)
                {
                    m_Direction = helpers::Direction::RIGHT;
                }
                else if (i == 38)
                {
                    m_Direction = helpers::Direction::UP;
                }
                else if (i == 40)
                {
                    m_Direction = helpers::Direction::DOWN;
                }
                else if (i == 27) // If the 'Esc' key was pressed
                {
                    m_OnPlay = false; // Finish the game
                }
            }
        }
    }
}

void controller_impl::ControllerImpl::initStartPositionOfFruit()
{
    // Generate coordinates
    m_LastFruitPosiotion.x = rand() % (m_SnakeModel->getValueOfXSize() - 5) + 3;
    m_LastFruitPosiotion.y = rand() % (m_SnakeModel->getValueOfYSize() - 5) + 3;

    // Mark generated coordinates as fruit
    m_SnakeModel->addPoint(m_LastFruitPosiotion.x, m_LastFruitPosiotion.y, helpers::tagsOfTheGameSpace::FRUIT);
}

void controller_impl::ControllerImpl::initStartPositionOfSnake()
{
    m_Viewer->resetSnake(); // Reset snake body to default state
    auto snake = m_Viewer->getAllSnakeBody(); // Get the default body
    m_SnakeModel->addPoint(snake[0].x, snake[0].y, helpers::tagsOfTheGameSpace::SNAKE_TAIL); // Mark the first coordinate as snake's tail
    m_SnakeModel->addPoint(snake[1].x, snake[1].y, helpers::tagsOfTheGameSpace::SNAKE_BODY); // Mark the second coordinate as snake's body
    m_SnakeModel->addPoint(snake[2].x, snake[2].y, helpers::tagsOfTheGameSpace::SNAKE_HEAD); // Mark the third coordinate as snake's head
}

void controller_impl::ControllerImpl::checkWall()
{
    auto head = m_Viewer->getHeadOfSnake();
    if (m_SnakeModel->getPoint(head.x, head.y) == helpers::tagsOfTheGameSpace::WALL)
    {
        m_OnPlay = false;
    }
}

void controller_impl::ControllerImpl::moveSnake()
{
    auto position = m_Viewer->getHeadOfSnake();
    m_SnakeModel->addPoint(position.x, position.y, helpers::tagsOfTheGameSpace::SNAKE_BODY); // It was head, now we made it body

    // Change the direction of the head
    if (m_Direction == helpers::Direction::RIGHT)
    {
        ++position.x;
    }
    else if (m_Direction == helpers::Direction::UP)
    {
        --position.y;
    }
    else if (m_Direction == helpers::Direction::LEFT)
    {
        --position.x;
    }
    else if (m_Direction == helpers::Direction::DOWN)
    {
        ++position.y;
    }

    // Set the new coordinate of the head
    m_Viewer->addPointOfBody(position); 
    m_SnakeModel->addPoint(position.x, position.y, helpers::tagsOfTheGameSpace::SNAKE_HEAD);
    // Delete the old tail
    position = m_Viewer->getTailOfSnake();
    m_SnakeModel->deletePoint(position.x, position.y);
    m_Viewer->removeOldTail();
    position = m_Viewer->getTailOfSnake();
    // Set the new tail
    m_SnakeModel->addPoint(position.x, position.y, helpers::tagsOfTheGameSpace::SNAKE_TAIL); // It was a body, now we made it a tail (end)
}

void controller_impl::ControllerImpl::ControllerImpl::checkFruit()
{
    auto headPosition = m_Viewer->getHeadOfSnake();
    auto tailPosition = m_Viewer->getTailOfSnake();

    if (headPosition.x == m_LastFruitPosiotion.x && headPosition.y == m_LastFruitPosiotion.y)
    {
        // Turn the tail of the snake to body of the snake
        m_SnakeModel->addPoint(tailPosition.x, tailPosition.y, helpers::tagsOfTheGameSpace::SNAKE_BODY);

        // Make the tail longer
        if (m_Direction == helpers::Direction::RIGHT)
        {
            --tailPosition.x;
        }
        else if (m_Direction == helpers::Direction::UP)
        {
            ++tailPosition.y;
        }
        else if (m_Direction == helpers::Direction::LEFT)
        {
            ++tailPosition.x;
        }
        else if (m_Direction == helpers::Direction::DOWN)
        {
            --tailPosition.y;
        }

        generateNewFruitPosition();
        m_Viewer->updateScore(10);
        // Mark the variable 'tailPosition' as the new tail
        m_Viewer->addPointOfBodyToBegin(tailPosition);
        m_SnakeModel->addPoint(tailPosition.x, tailPosition.y, helpers::tagsOfTheGameSpace::SNAKE_TAIL);
    }
    m_Viewer->updateLevel();
}

void controller_impl::ControllerImpl::generateNewFruitPosition()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    m_ValueOfXSize = m_SnakeModel->getValueOfXSize();
    m_ValueOfYSize = m_SnakeModel->getValueOfYSize();

    // When the snake ate the fruit, mark coordinates of the old fruit as coordinates of the snake's body
    m_SnakeModel->addPoint(m_LastFruitPosiotion.x, m_LastFruitPosiotion.y, helpers::tagsOfTheGameSpace::SNAKE_BODY);
    
    // Generate the new coordinates of the fruit
    m_LastFruitPosiotion.x = rand() % (m_ValueOfXSize - 2) + 1;
    m_LastFruitPosiotion.y = rand() % (m_ValueOfYSize - 2) + 1;

    
    // If the new coordinates of the fruit equal snake's coordinates
    while (!checkSnake())
    {
        // Generate the new coordinates of the fruit again
        m_LastFruitPosiotion.x = rand() % (m_ValueOfXSize - 2) + 1;
        m_LastFruitPosiotion.y = rand() % (m_ValueOfYSize - 2) + 1;
    }

    // If the new coordinates equal wall's coordinates
    if (checkEdges())
    {
        // Set the default coordinates
        m_LastFruitPosiotion.x = 5;
        m_LastFruitPosiotion.y = 7;
    }

    // Mark the new coordinates as fruit
    m_SnakeModel->addPoint(m_LastFruitPosiotion.x, m_LastFruitPosiotion.y, helpers::tagsOfTheGameSpace::FRUIT);
}

bool controller_impl::ControllerImpl::checkEdges() const
{
    return m_LastFruitPosiotion.x == 0 || 
        m_LastFruitPosiotion.x == m_ValueOfXSize - 1 || 
        m_LastFruitPosiotion.y == 0 || 
        m_LastFruitPosiotion.y == m_ValueOfYSize - 1;
}

void controller_impl::ControllerImpl::checkTail()
{
    auto head = m_Viewer->getHeadOfSnake();
    auto body = m_Viewer->getAllSnakeBody();

    for (size_t i = 0; i < body.size() - 1; ++i)
    {
        if (body[i].x == head.x && body[i].y == head.y)
        {
            m_OnPlay = false;
        }
    }
}

bool controller_impl::ControllerImpl::checkSnake() const
{
    auto snakeBody = m_Viewer->getAllSnakeBody();

    for (const auto& i : snakeBody)
    {
        if (i.x == m_LastFruitPosiotion.x && i.y == m_LastFruitPosiotion.y)
        {
            return false;
        }
    }
    return true;
}
