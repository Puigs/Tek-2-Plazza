/*
** EPITECH PROJECT, 2020
** Plazza
** File description:
** SafeQueue.hpp
*/

#ifndef SAFEQUEUE_HPP_
#define SAFEQUEUE_HPP_

#include "thread.hpp"

template<class T>
class interface {
    public:
        virtual ~interface (void) = default;
    public:
        virtual void        push    (T &&val)   = 0;
        virtual bool        trypop  (T &&value) = 0;
        virtual T           pop     (void)      = 0;
        virtual size_t      size    (void)      = 0;
};

template<class T>
class SafeQueue {
    private:
        std::queue<T>           _sQ;
        std::mutex              _mutex;
        std::condition_variable _condVar;
        long                    _maxLockTime;
    public:
        SafeQueue   (long maxLockTime = 5000) : _mutex(), _condVar(), _maxLockTime(maxLockTime)
            {
            }
        ~SafeQueue  (void)
            {
            }
    public:
        void push (T &val)
            {
                std::unique_lock<std::mutex>    lck(_mutex);

                _sQ.push(val);
                _condVar.notify_one();
            }
        void push (const T &&val)
            {
                std::unique_lock<std::mutex>    lck(_mutex);

                _sQ.push(val);
                _condVar.notify_one();
            }
        SafeQueue<T> & operator+(const T &val)
            {
                std::unique_lock<std::mutex>    lck(_mutex);

                _sQ.push(val);
                _condVar.notify_one();
                return (*this);
            }
        SafeQueue<T> & operator+(const T &&val)
            {
                std::unique_lock<std::mutex>    lck(_mutex);

                _sQ.push(val);
                _condVar.notify_one();
                return (*this);
            }
        SafeQueue<T> & operator+=(const T &val)
            {
                std::unique_lock<std::mutex>    lck(_mutex);

                _sQ.push(val);
                _condVar.notify_one();
                return (*this);
            }
        SafeQueue<T> & operator+=(const T &&val)
            {
                std::unique_lock<std::mutex>    lck(_mutex);

                _sQ.push(val);
                _condVar.notify_one();
                return (*this);
            }
        bool trypop (T &value)
            {
                if (_mutex.try_lock()) {
                    if (_sQ.size() == 0) {
                        _mutex.unlock();
                        return false;
                    }
                    value = _sQ.front();
                    _sQ.pop();
                    _mutex.unlock();
                    return true;
                }
                return false;
            }
        
        bool trypop (T &value, size_t time)
            {
                std::unique_lock<std::mutex>    lck(_mutex);
                if (_sQ.size() == 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(time));
                    if (_sQ.size() == 0) {
                        return (false);
                    }
                }
                value = _sQ.front();
                _sQ.pop();
                return true;
            }

        bool pop (T &value)
            {
                std::unique_lock<std::mutex>    lck(_mutex);

                if (_sQ.size() == 0) {
                    _condVar.wait_for(lck, std::chrono::milliseconds(_maxLockTime), [&]{return (_sQ.size() > 0);});
                    if (_sQ.size() == 0)
                        return (false);
                }
                value = _sQ.front();
                _sQ.pop();
                return true;
            }

        size_t size (void)
            {
                std::unique_lock<std::mutex>    lock(_mutex);

                return _sQ.size();
            }
};

#endif /* !SAFEQUEUE_HPP_ */
