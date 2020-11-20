/*
** EPITECH PROJECT, 2020
** loop.cpp
** File description:
** loop
*/

#include "../include/my.hpp"

void send_status(Server_Master sock)
{
    std::vector<int> listFD = sock.getFDS();
    message_t *dest = new message_t;
    dest->cmd = 5;
    dest->pizzaSize = 0;
    dest->pizzaType = 0;
    dest->response = 0;
    dest->bakingMultiplier = 0;

    for (size_t i = 0; i < listFD.size(); i++) {
        sock.send(listFD[i], dest);
    }
}

/*std::vector<Process> call_close(std::vector<Process> map, data_t data, int fd)
{
    
    close(fd);
}*/

void call_send(std::vector<message_t *> array, Server_Master sock)
{
    int tmp = array[0]->cmd;
    array[0]->cmd = 2;
    std::vector<int> listFD = sock.getFDS();

    for (size_t i = 0; i < listFD.size(); i++) {
        sock.send(listFD[i], array[0]);
    }
    array[0]->cmd = tmp;
}

std::map<int, data_t> call_response(std::map<int, data_t> map, data_t &data)
{
    if (data.data->cmd == 4) {
        map[data.fd] = data;
    }
    return map;
}

void loop(Param &param, Parser &parser)
{
    Loop loop(param, parser);

    loop.do_loop();
}