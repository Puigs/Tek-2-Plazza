/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** my
*/

#ifndef MY_H_
#define MY_H_

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
#include "Loop.hpp"

int check_arg(int ac, char **av);
void init_obj(char **av);
void loop(Param &param, Parser &parser);
std::vector<Process> init_send(std::vector<Process> map, std::map<int, data_t> rMap, Server_Master &sock, std::vector<message_t *> array, Param &param, int fd);
std::map<int, data_t> call_response(std::map<int, data_t> map, data_t &data);

#endif /* !MY_H_ */
