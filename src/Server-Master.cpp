/*
** EPITECH PROJECT, 2020
** Server-Master.cpp
** File description:
** Server-Master
*/

#include "../include/Server-Master.hpp"

Server_Master::Server_Master()
{
    _cMax = 100;
    _sFd.push_back(0);
    tmp = (message_t *) malloc(sizeof(message_t));

    _fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (_fd <= 0) {
        if (close(_fd) == -1) {
            perror("Close");
        }
        perror("Init Socket failed");
        exit(EXIT_FAILURE);
    }

    memset(&_addr, 0, sizeof(_addr));
    _addr.sun_family = AF_UNIX;
    strcpy(_addr.sun_path, "Server");

    if ((bind(_fd, (struct sockaddr *)&_addr, SUN_LEN(&_addr)) < 0)) {
        if (close(_fd) == -1) {
            perror("Close");
        }
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(_fd, _cMax) < 0) {
        if (close(_fd) == -1) {
            perror("Close");
        }
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
}

Server_Master::~Server_Master()
{

}

void Server_Master::send(int fd, __attribute__((unused)) message_t *data)
{
    write(fd, data, sizeof(*data));
}

data_t Server_Master::do_select()
{
    int new_sock = 0;
    int size = 0;
    struct timeval tv = {1,50};
    data_t data;

    data.status = 0;
    FD_ZERO(&fds);
    FD_SET(_fd, &fds);
    max_sd = _fd;
    for (size_t i = 0; i < _cMax && i < _sFd.size(); i++) {
        sd = _sFd[i];
        if (sd >= 0)
            FD_SET(sd, &fds);
        if (sd >= max_sd)
            max_sd = sd;
    }
    if (select(_cMax + 1, &fds, NULL, NULL, &tv) < 0) {
        perror("select");
        exit (EXIT_FAILURE);
    }
    if (FD_ISSET(_fd, &fds)) {
        size = sizeof(_sockAdr);
        new_sock = accept(_fd, NULL, NULL);
        if (new_sock < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
        std::cout << "New kitchen create and connected"  << std::endl;
        _sFd.push_back(new_sock);
        data.fd = new_sock;
        data.status = 3;
        return data;
    }
    for (size_t i = 0; i < _cMax && i < _sFd.size(); i++) {
        sd = _sFd[i];
        if (FD_ISSET(sd, &fds)) {
            if (sd == 0) {
                char buff[4097] = {0};
                size = read(sd, &buff, 4096);
                std::string buffer(buff);
                buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
                data.status = 1;
                data.buffer = buffer;
                return data;
            } else if (size == -1)
                break;
            tmp = new message_t;
            size = read(sd, tmp, sizeof(message_t));
            data.status = 2;
            data.fd = sd;
            data.data = tmp;
            if (data.data->cmd == 2) {
                _sFd.erase(_sFd.begin() + i);
            }
            return data;
        }
    }
    return data;
}

int Server_Master::getFD()
{
    return _fd;
}

std::vector<int> Server_Master::getFDS()
{
    std::vector<int> tmp = _sFd;
    
    for (size_t i = 0; i < tmp.size(); i++) {
        //std::cout << tmp[i] << std::endl;
        if (tmp[i] == 0) {
            tmp.erase(tmp.begin() + i);
            break;
        }
    }
    return tmp;
}