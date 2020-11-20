/*
** EPITECH PROJECT, 2020
** Plazza
** File description:
** ThreadPool.hpp
*/

#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_


#include <list>
#include "thread.hpp"
#include "MyThread.hpp"
#include "SafeQueue.hpp"
#include "SafeMap.hpp"
#include "Pizza.hpp"
#include "Regina.hpp"
#include "Americana.hpp"
#include "Margarita.hpp"
#include "Fantasia.hpp"
#include "Regina.hpp"

class ThreadPool {
    private:
        std::vector<MyThread>           _pool;
        std::vector<std::atomic<bool>>  _taskState;
        SafeQueue<Pizza>                _cmd;
        SafeQueue<Pizza>                _endedCmd;
        std::map<size_t, bool>          _freeThread;
        long                            _MaxIdl;
        size_t                          _maxCmdSize;
    public:
        ThreadPool(size_t size, long maxIdl) :
                _pool(size),
                _taskState(size),
                _cmd(maxIdl),
                _endedCmd(maxIdl),
                _MaxIdl(maxIdl),
                _maxCmdSize(size * 2)
            {
                for (size_t idx = 0, end = _pool.size(); idx < end; ++idx) {
                    _taskState[idx] = false;
                    _freeThread[idx] = true;
                }
            }

        ~ThreadPool(void)
            {
            }

    public:
        template<typename Task, typename... Args>
        bool addTask (Task &&task, Args &&...args)
            {
                ssize_t idx = -1;
                std::map<size_t, bool>::iterator it = _freeThread.begin();

                while (it != _freeThread.end()) {
                    if (it->second == true) {
                        idx = it->first;
                        break;
                    }
                    ++it;
                }
                if (idx == -1) {
                    return (false);
                }
                _freeThread[idx] = false;
                return (_pool[idx].newTask(task, args..., &_taskState[idx]));
            }

        size_t getActive(void)
            {
                size_t idx = 0;
                size_t end = _taskState.size();
                size_t val = 0;

                while (idx < end) {
                    if (_taskState[idx] == true)
                        ++val;
                    ++idx;
                }
                return (val);
            }

        size_t getEndedThread(void)
            {
                ssize_t count = 0;

                for (size_t idx = 0, end = _pool.size(); idx < end; ++idx) {
                    if (_pool[idx].updateState() == MyThread::State::ENDED) {
                        ++count;
                        _freeThread[idx] = true;
                    }
                }
                return count;
            }

        void getCookedPizza(void) {
            while (_endedCmd.size())
            {
                    Pizza p;
                    if (_endedCmd.trypop(p) == false)
                        break;
                }
            }

        bool addCmd(Pizza &pizza)
            {
                if (_cmd.size() >= _maxCmdSize)
                    return (false);
                _cmd.push(pizza);
                return (true);
            }
        
        void joinAllThread(void)
            {
                for (size_t idx = 0; idx < _pool.size(); ++idx) {
                    _pool[idx].waitEnd();
                }
            }

        size_t getWaitingCmdSize(void)
            {
                return (_cmd.size());
            }
        
        void cook(
                SafeMap<Pizza::Ingredients> *stock,
                std::atomic<bool> *exit,
                std::atomic<bool> *busy,
                std::atomic<bool> *ended)
            {
                Pizza p;
                while (*exit != true) {
                    if (this->_cmd.trypop(p) == false) {
                        if (*exit == true)
                            break;
                        else {
                            std::this_thread::sleep_for(std::chrono::milliseconds(1));
                            continue;
                        }
                    }
                    *busy = true;

                    std::vector<Pizza::Ingredients> compo = p.getIngredients();
                    for (register size_t idx = 0; idx < compo.size(); ++idx) {
                        if (stock->absDec(compo[idx]) == false && *exit == true)
                            break;
                    }
                    if (*exit == true)
                        break;
                    std::this_thread::sleep_for(std::chrono::milliseconds(p.getBakingTime()));
                    {
                        _endedCmd.push(p);
                    }
                    *busy = false;
                }
                *ended = true;
            }
};

#endif /* !THREADPOOL_HPP_ */