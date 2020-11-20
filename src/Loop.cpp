/*
** EPITECH PROJECT, 2020
** Loop.cp
** File description:
** Loop
*/

#include "../include/Loop.hpp"

Loop::Loop(Param &param, Parser &parser)
{
    _param = param;
    _parser = parser;
}

Loop::~Loop()
{
}

void Loop::do_loop()
{
    while (1) {
        if (check == 0) {
            write(1, "> ", 2);
            check = 1;
        }
        data = sock.do_select();
        if (data.status == 0) {
            continue;
        }
        if (data.status == 1 && data.buffer == "exit") {
                unlink("Server");
                exit(0);
        } else if (data.status == 1 && data.buffer == "status") {
            if (map.empty()) {
                std::cout << "Nobody working" << std::endl;
                check = 0;
            } else {
                Loop::call_status();
                sleep(2);
                check = 0;
            }
            continue;
        } else if (data.status == 1) {
            _parser.setCmd(data.buffer);
            _array = _parser.getCmd();
            if (_array.empty()) {
                check = 0;
                continue;
            }
            if (map.empty()) {
                kit = new Kitchen(fd, _param.getNcook(), _param.getTimer());
                pro = new Process(*kit);
                data = sock.do_select();
                arrayFD.push_back(data.fd);
                map.push_back(pro);
            }
            Loop::call_send();
            inProgress = 1;
            _inProgressArray = _array;
            continue;
        }
        if (data.status == 2 && data.data != NULL && data.data->cmd == 2) {
            call_close();
        }
        if (data.status == 2 && data.data != NULL && data.data->cmd == 3)
            Loop::call_response(data);
        if (inProgress == 1 && rMap.size() == map.size()) {
            inProgress = 0;
            Loop::init_send();
            _inProgressArray.clear();
            rMap.clear();
            check = 0;
        }
    }    
}

void Loop::call_send()
{
    std::vector<int> listFD = sock.getFDS();
    message_t *dest = new message_t();
    dest->cmd = 3;
    dest->pizzaSize = 0;
    dest->pizzaType = 0;
    dest->response = 0;
    dest->bakingMultiplier = 0;
    dest->magic = 0x42424242;

    for (size_t i = 0; i < listFD.size(); i++) {
        sock.send(listFD[i], dest);
    }
}

void Loop::call_status()
{
    std::vector<int> listFD = sock.getFDS();
    message_t *dest = new message_t();
    dest->cmd = 4;
    dest->pizzaSize = 0;
    dest->pizzaType = 0;
    dest->response = 0;
    dest->bakingMultiplier = 0;
    dest->magic = 0x42424242;

    for (size_t i = 0; i < listFD.size(); i++) {
        sock.send(listFD[i], dest);
    }
}

void Loop::call_response(data_t &data)
{
    if (data.data->cmd == 3) {
        rMap[data.fd] = data;
    }
}

void Loop::call_close()
{
    size_t i = 0;

    for (; i < map.size(); i++) {
        if (arrayFD[i] == data.fd) {
            arrayFD.erase(arrayFD.begin() + i);
            map.erase(map.begin() + i);
            break;
        }
    }
    close(data.fd);
}

int Loop::find_small(std::vector<int> listFD)
{
    int ret = 0;
    
    if (listFD.empty())
        return -1;
    ret = listFD[0];
    for (size_t i = 1; i < listFD.size(); i++) {
        if (rMap[listFD[i]].data->response == 0)
            continue;
        if (rMap[ret].data->response < rMap[listFD[i]].data->response)
            ret = listFD[i];
    }
    if (rMap[ret].data->response == 0)
        return -1;
    return ret;
}

void Loop::init_send()
{
    int tmp = 0;
    std::vector<int> listFD = sock.getFDS();

    for (size_t i = 0; i < _inProgressArray.size(); i++) {
        tmp = Loop::find_small(listFD);
        if (tmp == -1) {
            kit = new Kitchen(fd, _param.getNcook(), _param.getTimer());
            pro = new Process(*kit);
            data = sock.do_select();
            arrayFD.push_back(data.fd);
            map.push_back(pro);
            listFD = sock.getFDS();
            data.data = new message_t();
            data.data->response = _param.getNcook();
            data.data->cmd = 3;
            Loop::call_response(data);
            tmp = Loop::find_small(listFD);
        }
        sock.send(tmp, _inProgressArray[i]);
        rMap[tmp].data->response -= 1;
    }
}