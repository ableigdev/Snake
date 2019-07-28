#include <conio.h>
#include "AutoPlayControllerImpl.h"
#include "ThreadWrapper.h"
#include "constants.h"

controller_impl::AutoPlayControllerImpl::AutoPlayControllerImpl(std::unique_ptr<interfaces::IViewer>&& viewer,
    std::unique_ptr<interfaces::ISnakeModel>&& model)
    : ControllerImpl(std::move(viewer), std::move(model))
{

}

size_t controller_impl::AutoPlayControllerImpl::play()
{
    m_OnPlay = true;
    initStartPositionOfFruit();
    initStartPositionOfSnake();

    helpers::ThreadWrapper wrapper(std::thread(&AutoPlayControllerImpl::catchUserInput, this));
    helpers::ThreadWrapper escapeWrapper2(std::thread([this]() // Catch the case, when a user press 'Esc' key
    {
        while (m_OnPlay)
        {
            if (GetAsyncKeyState(27) == -32767) // If 'Esc' pressed
            {
                m_OnPlay = false; // Finish autoplay mode
            }
        }
    }));

    while (m_OnPlay)
    {
        checkWall();
        checkTail();
        moveSnake();
        checkFruit();
        m_Viewer->draw(*m_SnakeModel);
        m_Viewer->showData();
    }

    return m_Viewer->score();
}

// Override the 'catchUserInput' method
void controller_impl::AutoPlayControllerImpl::catchUserInput()
{
    while (m_OnPlay)
    {
        getCurrentHeadPosition();
        follow();
    }
}

void controller_impl::AutoPlayControllerImpl::getCurrentHeadPosition()
{
    auto head = m_Viewer->getHeadOfSnake();
    m_CurrentSnakePosition.x = head.x;
    m_CurrentSnakePosition.y = head.y;
}

// Change direction independence from the position of the fruit
void controller_impl::AutoPlayControllerImpl::follow()
{
    if (m_LastFruitPosiotion.x > m_CurrentSnakePosition.x)
    {
        m_Direction = helpers::Direction::RIGHT;
    }
    
    if (m_LastFruitPosiotion.y > m_CurrentSnakePosition.y)
    {
        m_Direction = helpers::Direction::DOWN;
    }

    if (m_LastFruitPosiotion.x < m_CurrentSnakePosition.x)
    {
        m_Direction = helpers::Direction::LEFT;
    }

    if (m_LastFruitPosiotion.y < m_CurrentSnakePosition.y)
    {
        m_Direction = helpers::Direction::UP;
    }

    Sleep(5);
}