#ifndef SNAKE_AUTOPLAYCONTROLLERIMPL_H
#define SNAKE_AUTOPLAYCONTROLLERIMPL_H

#include "ControllerImpl.h"

namespace controller_impl
{
    // Inherit from the ControllerImpl class
    // The AutoPlayControllerImpl class is a simple sample
    // which demonstrates primitive autoplay or computer play mode
    class AutoPlayControllerImpl : public ControllerImpl
    {
    public:
        AutoPlayControllerImpl(std::unique_ptr<interfaces::IViewer>&& viewer, 
            std::unique_ptr<interfaces::ISnakeModel>&& model);
        virtual ~AutoPlayControllerImpl() override = default;

        virtual size_t play() override;

    protected:
        void catchUserInput();

    private:
        void getCurrentHeadPosition();
        void follow();

    private:
        POINT m_CurrentSnakePosition;
    };
}

#endif // SNAKE_AUTOPLAYCONTROLLERIMPL_H
