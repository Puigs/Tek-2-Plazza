/*
** EPITECH PROJECT, 2020
** Server-Master.hpp
** File description:
** Server-Master
*/

#ifndef Server_Master_HPP_
#define Server_Master_HPP_

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
#include <sys/un.h>
#include <sys/ipc.h>
#include "Client.hpp"
#include <algorithm>

class Server_Master {
    public:
        Server_Master();
        ~Server_Master();
        data_t do_select();
        void send(int fd, message_t *data);
        int getFD();
        std::vector<int> getFDS();
        void do_connect(int fd);

    protected:
    private:
        std::vector<int> _sFd;
        size_t _cMax;
        int _fd;
        struct sockaddr_in _sockAdr;
        struct sockaddr _sock;
        socklen_t _sock_size;
        struct sockaddr_un _addr;
        //For select
        fd_set fds;
        int sd = 0;
        int max_sd = 0;
        message_t *tmp;
        std::string empty;
};

#endif /* !Server_Master_HPP_ */
