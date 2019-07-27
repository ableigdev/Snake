#include "ThreadWrapper.h"

helpers::ThreadWrapper::ThreadWrapper(std::thread&& t)
    : m_Thread(std::move(t))
{

}

helpers::ThreadWrapper::~ThreadWrapper()
{
    if (m_Thread.joinable())
    {
        m_Thread.join();
    }
}

std::thread& helpers::ThreadWrapper::get()
{
    return m_Thread;
}