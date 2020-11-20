/*
** EPITECH PROJECT, 2020
** Plazza
** File description:
** MyThread.hpp
*/

#ifndef MYTHREAD_HPP_
#define MYTHREAD_HPP_

#include "thread.hpp"

class MyThread {
    public:
        enum State {STARTED, RUNNING, ENDED};
    private:
        std::thread         _thread;
        MyThread::State     _state;
        std::atomic<bool>   _end;
    public:
        template<typename Task, typename... Args>
        bool newTask (Task &&task, Args &&...args)
            {
                bool ret = _end;

                if (_end) {
                    _end = false;
                    _thread = std::thread(task, args..., &_end);
                    if (_thread.joinable())
                        _thread.detach();
                    _state = MyThread::State::RUNNING;
                }
                return (ret);
            }

        template<typename Task, typename... Args>
        bool newLambda (Task &&task, Args ...args)
            {
                bool ret = _end;

                if (_end) {
                    _end = false;
                    _thread = std::thread(task, args...);
                // if (_thread.joinable())
                //     _thread.detach();
                }
                return (ret);
            }

        MyThread::State updateState (void)
            {
                if (_end == true)
                    _state = MyThread::State::ENDED;
                else
                    _state = MyThread::State::RUNNING;
                return (_state);
            }

        void waitEnd (void)
            {
                if (_thread.joinable())
                    _thread.join();
            }
    public:\
        MyThread(void) : _state(MyThread::State::STARTED), _end(true)
            {
            }
        ~MyThread (void)
            {
                // _thread.join();
                if (_thread.joinable())
                    _thread.join();
                    // _thread.detach();
            }
};

#endif /* !MYTHREAD_HPP_ */