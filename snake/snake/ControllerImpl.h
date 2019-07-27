#ifndef SNAKE_CONTROLLERIMPL_H
#define SNAKE_CONTROLLERIMPL_H

#include <memory>
#include <random>
#include "IController.h"
#include "IViewer.h"
#include "ISnakeModel.h"

namespace controller_impl
{
    // Implement the IController interface
    class ControllerImpl : public interfaces::IController
    {
    public:
        ControllerImpl(std::unique_ptr<interfaces::IViewer>&& viewer, std::unique_ptr<interfaces::ISnakeModel>&& model);
        
        virtual ~ControllerImpl() override = default;
        virtual size_t play() override;

    protected:
        void catchUserInput();
        void initStartPositionOfFruit();
        void initStartPositionOfSnake();
        void checkWall();
        void moveSnake();
        void checkFruit();
        inline bool checkEdges() const;
        void checkTail();
        bool checkSnake() const;

    private:
        void generateNewFruitPosition();

    protected:
        std::unique_ptr<interfaces::IViewer> m_Viewer;
        std::unique_ptr<interfaces::ISnakeModel> m_SnakeModel;
        int m_Direction {};
        bool m_OnPlay = false;
        POINT m_LastFruitPosiotion { 0, 0 };
        size_t m_ValueOfXSize {};
        size_t m_ValueOfYSize {};
    };
}

#endif // SNAKE_CONTROLLERIMPL_H
