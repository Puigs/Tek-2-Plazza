/*
** EPITECH PROJECT, 2020
** Plazza
** File description:
** Thread.hpp
*/

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <chrono>
#include <array>
#include <vector>
#include <map>
#include <queue>
#include <unistd.h>
#include <cstdlib>
#include <atomic>

typedef std::chrono::_V2::high_resolution_clock::time_point        myClock;
#define getTime() std::chrono::high_resolution_clock::now()
#define getTimeElapsed(t) std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - t).count()
#endif /* !THREAD_HPP_ */
