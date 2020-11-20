/*
** EPITECH PROJECT, 2020
** Loop.hpp
** File description:
** Loop
*/

#ifndef LOOP_HPP_
#define LOOP_HPP_

#include "data.hpp"
#include "Error.hpp"
#include "Param.hpp"
#include "Parser.hpp"
#include <iostream>
#include <unistd.h>
#include "Server-Master.hpp"
#include "Pizza.hpp"
#include <stdlib.h>
#include "Client.hpp"
#include "Process.hpp"
#include "SafeMap.hpp"
#include "SafeQueue.hpp"
#include "ThreadPool.hpp"
#include "MyThread.hpp"
#include <map>

class Loop {
    public:
        Loop(Param &param, Parser &parser);
        ~Loop();
        void do_loop();
        void call_send();
        void call_status();
        void call_response(data_t &data);
        void init_send();
        int find_small(std::vector<int> listFD);
        void call_close();


    protected:
    private:
        std::vector<message_t *> _array;
        std::vector<message_t *> _inProgressArray;
        std::vector<Process *> map;
        std::vector<int> arrayFD;
        Kitchen *kit;
        Process *pro;
        std::map<int, data_t> rMap;
        data_t data;
        int fd = sock.getFD();
        int check = 0;
        int inProgress = 0;
        Param _param;
        Parser _parser;
        Server_Master sock;
};

#endif /* !LOOP_HPP_ */
