#ifndef SNAKE_THREADWRAPPER_H
#define SNAKE_THREADWRAPPER_H

#include <thread>

namespace helpers
{
    class ThreadWrapper
    {
    public:
        ThreadWrapper(std::thread&& t);
        ~ThreadWrapper();

        std::thread& get();

    private:
        std::thread m_Thread;
    };
}

#endif // SNAKE_THREADWRAPPER_H
