/*
** EPITECH PROJECT, 2020
** utils.cpp
** File description:
** utils
*/

#include "../include/my.hpp"

int find_small(std::vector<int> listFD, std::map<int, data_t> rMap)
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

std::vector<Process> init_send(std::vector<Process> map, std::map<int, data_t> rMap, Server_Master &sock, std::vector<message_t *> array, Param &param, int fd)
{
    std::vector<int> listFD = sock.getFDS();
    int tmp = 0;
    Process *pro;
    Kitchen *kit;
    data_t data;

    for (size_t i = 0; i < array.size(); i++) {
        tmp = find_small(listFD, rMap);
        if (tmp == -1) {
            kit = new Kitchen(fd, param.getNcook(), param.getTimer());
            pro = new Process(*kit);
            data = sock.do_select();
            map.push_back(*pro);
            listFD = sock.getFDS();
            data.data = new message_t;
            data.data->response = param.getNcook();
            data.data->cmd = 4;
            rMap = call_response(rMap, data);
            tmp = find_small(listFD, rMap);
        }
        sock.send(tmp, array[i]);
        rMap[tmp].data->response -= 1;
    }
    return map;
}