/*
** EPITECH PROJECT, 2020
** Client.hpp
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <vector>
#include <unistd.h>
#include "data.hpp"
#include <string.h>
#include <sys/un.h>
#include <sys/ipc.h>
#include <algorithm>

class Client {
    public:
        Client();
        Client(int fd);
        Client(const Client &c);
        Client &operator=(const Client &client);
        ~Client();
        message_t *getMessage();
        void send(message_t *data);
        int getFD();


    protected:
    private:
        int _fd;
        int _pFd;
        struct sockaddr_in _sockAdr;
        struct sockaddr _sock;
        struct sockaddr_un _addr;
        socklen_t _sock_size;
};

#endif /* !CLIENT_HPP_ */
