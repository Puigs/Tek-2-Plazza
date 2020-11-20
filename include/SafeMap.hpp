/*
** EPITECH PROJECT, 2020
** Plazza
** File description:
** SafeMap.hpp
*/

#ifndef SAFEMAP_HPP_
#define SAFEMAP_HPP_

#include "../include/thread.hpp"

template<class K/*, class V*/>
class SafeMap {
    private:
        std::map<K, std::size_t/*V*/>_container;
        std::mutex                  _mutex;
        std::condition_variable     _condVar;
        long                        _MaxWait;
    public:
        SafeMap (long maxWait = 1000l) : _MaxWait(maxWait)
            {
            }
        ~SafeMap   (void)
            {
            }
    public:
        const std::map<K, std::size_t> &  operator[](const K &key)
            {
                std::unique_lock<std::mutex>    lock(_mutex);

                return (_container[key]);
            }

        const std::map<K, std::size_t> &  operator[](const K &&key)
            {
                std::unique_lock<std::mutex>    lock(_mutex);

                return (_container[key]);
            }

        void    push    (const K &key,/* const V*/std::size_t &value)
            {
                std::unique_lock<std::mutex>    lock(_mutex);

                _container[key] = value;
                _condVar.notify_one();
            }

        void    push    (const K &key,/* const V*/std::size_t &&value)
            {
                std::unique_lock<std::mutex>    lock(_mutex);

                _container[key] = value;
                _condVar.notify_one();
            }

        void    push    (const K &&key,/* const V*/std::size_t &value)
            {
                std::unique_lock<std::mutex>    lock(_mutex);

                _container[key] = value;
                _condVar.notify_one();
            }

        void    push    (const K &&key,/* const V*/std::size_t &&value)
            {
                std::unique_lock<std::mutex>    lock(_mutex);

                _container[key] = value;
                _condVar.notify_one();
            }

        bool    tryGet  (const K &key,/* V*/ std::size_t &value)
            {
                std::unique_lock<std::mutex>                lock(_mutex);
                typename std::map<K, std::size_t/*, V*/>::const_iterator it =_container.find(key);

                if (it == _container.end())
                    return (false);
                value = _container[key];
                return (true);
            }

        bool    tryGet  (const K &&key,/* V*/ std::size_t &value)
            {
                std::unique_lock<std::mutex>                lock(_mutex);
                typename std::map<K, std::size_t/*, V*/>::const_iterator it =_container.find(key);

                if (it == _container.end())
                    return (false);
                value = _container[key];
                return (true);
            }   

        bool erase  (const K &key)
            {
                std::unique_lock<std::mutex>                lock(_mutex);
                typename std::map<K, std::size_t/*, V*/>::const_iterator it =_container.find(key);

                if (it == _container.end())
                    return (false);
                _container.erase(key);
                return true;
            }

        bool   erase (const K &&key)
            {
                std::unique_lock<std::mutex>                lock(_mutex);
                typename std::map<K, std::size_t/*, V*/>::const_iterator it =_container.find(key);

                if (it == _container.end())
                    return (false);
                _container.erase(key);
                return true;
            }

        const std::size_t &   at  (const K &key)
            {
                std::unique_lock<std::mutex>    lock(_mutex);

                return (_container[key]);
            }
        const std::size_t &   at  (const K &&key)
            {
                std::unique_lock<std::mutex>    lock(_mutex);

                return (_container[key]);
            }

        bool    inc     (const K &key)
            {
                std::unique_lock<std::mutex>    lock(_mutex);
                typename std::map<K, std::size_t/*, V*/>::const_iterator it = _container.find(key);

                if (it.first == _container.end())
                    return (false);
                _container[key] += 1;
                return (true);
            }

        bool    inc     (const K &&key)
            {
                std::unique_lock<std::mutex>    lock(_mutex);
                typename std::map<K, std::size_t/*, V*/>::const_iterator it = _container.find(key);

                if (it == _container.end())
                    return (false);
                _container[key] += 1;
                _condVar.notify_one();
                return (true);
            }

        bool    inc     (const K &key, std::size_t val)
            {
                std::unique_lock<std::mutex>    lock(_mutex);
                typename std::map<K, std::size_t/*, V*/>::const_iterator it = _container.find(key);

                if (it == _container.end())
                    return (false);
                _container[key] += val;
                _condVar.notify_one();
                return (true);
            }

        bool    inc     (const K &&key, std::size_t val)
            {
                std::unique_lock<std::mutex>    lock(_mutex);
                typename std::map<K, std::size_t/*, V*/>::const_iterator it = _container.find(key);

                if (it == _container.end())
                    return (false);
                _container[key] += val;
                _condVar.notify_one();
                return (true);
            }

        bool    dec     (const K &key)
            {
                std::unique_lock<std::mutex>    lock(_mutex);
                typename std::map<K, std::size_t>::const_iterator it = _container.find(key);

                if (it == _container.end())
                    return (false);
                _container[key] -= 1;
                return (true);
            }

        bool    dec     (const K &&key)
            {
                std::unique_lock<std::mutex>    lock(_mutex);
                typename std::map<K, std::size_t/*, V*/>::const_iterator it = _container.find(key);
            
                if (it == _container.end())
                    return (false);
                _container[key] -= 1;
                return (true);
            }

        bool    dec     (const K &key, std::size_t val)
            {
                std::unique_lock<std::mutex>    lock(_mutex);
                typename std::map<K, std::size_t>::const_iterator it = _container.find(key);

                if (it == _container.end())
                    return (false);
                _container[key] -= val;
                return (true);
            }

        bool    dec     (const K &&key,std::size_t val)
    {
        std::unique_lock<std::mutex>    lock(_mutex);
        typename std::map<K, std::size_t>::const_iterator it = _container.find(key);

        if (it == _container.end())
            return (false);
        _container[key] -= val;
        return (true);
    }

        bool    absDec  (const K &key)
            {
               std::unique_lock<std::mutex>    lock(_mutex);
               typename std::map<K, std::size_t>::const_iterator it = _container.find(key);

               if (it == _container.end())
                   return (false);
               if (_container[key] < 1) {
                   _condVar.wait_for(lock, std::chrono::milliseconds(_MaxWait), [&, key]{return (_container[key] > 0);});
                   if (_container[key] < 1)
                       return (false);
               }
               _container[key] -= 1;
               return (true);
            }


        bool    absDec  (const K &&key)
            {
                std::unique_lock<std::mutex>    lock(_mutex);
                typename std::map<K, std::size_t/*, V*/>::const_iterator it = _container.find(key);

                if (it == _container.end())
                    return (false);
                if (_container[key] < 1) {
                    _condVar.wait_for(lock, std::chrono::milliseconds(_MaxWait), [&, key]{return (_container[key] > 0);});
                    if (_container[key] < 1)
                        return (false);
                }
                _container[key] -= 1;
                return (true);
            }

        bool    absDec  (const K &key,/* V*/std::size_t val)
            {
                std::unique_lock<std::mutex>    lock(_mutex);
                typename std::map<K, std::size_t/*, V*/>::const_iterator it = _container.find(key);

                if (it == _container.end())
                    return (false);
                if (_container[key] < val) {
                    _condVar.wait_for(lock, std::chrono::milliseconds(_MaxWait), [&, key, val]{return (_container[key] >= val);});
                    if (_container[key] < 1)
                        return (false);
                }
                _container[key] -= val;
                return (true);
            }

        bool    absDec  (const K &&key,/* V*/std::size_t val)
            {
                std::unique_lock<std::mutex>    lock(_mutex);
                typename std::map<K, std::size_t/*, V*/>::const_iterator it = _container.find(key);
            
                if (it == _container.end())
                    return (false);
                if (_container[key] < val) {
                    _condVar.wait_for(lock, std::chrono::milliseconds(_MaxWait), [&, key, val]{return (_container[key] >= val);});
                    if (_container[key] < 1)
                        return (false);
                }
                _container[key] -= val;
                return (true);
            }
};

#endif /* !SAFEMAP_HPP_ */
