/*
** EPITECH PROJECT, 2020
** Kitchen.hpp
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <map>
#include <iostream>
#include <chrono>
#include <ctime>
#include "Pizza.hpp"
#include "SafeQueue.hpp"
#include "SafeMap.hpp"
#include "ThreadPool.hpp"
#include "MyThread.hpp"
#include "Client.hpp"


typedef std::chrono::_V2::high_resolution_clock::time_point myClock;

class Kitchen {
    public:
        Kitchen(u_int32_t fd, u_int32_t cookNb, u_int32_t stockMultiplier);
        ~Kitchen();
        void refillStocks();
        void checkActivity();
        void bakePizza(message_t *message);
        void canBakePizza(message_t *message);
        void closeKitchen(message_t *message);
        void getInactiveCooksNb(message_t *message);
        void parseCommands(message_t *command);
        void kitchenStatus(message_t *command);
        void start();
        Client getSock();
    protected:
    private:
        u_int32_t _fd;
        u_int32_t _cookNb;
        u_int32_t _stockMultiplier;
        u_int32_t _kitchenLifeTime;
        std::atomic<bool> _dead;
        SafeMap<Pizza::Ingredients> *_stocks;
        std::map<Command, void (Kitchen::*)(message_t *)> _commandsActions;
        ThreadPool *_cooks;
        myClock _activityClock;
        Client *_comm;
};

#endif /* !KITCHEN_HPP_ */
