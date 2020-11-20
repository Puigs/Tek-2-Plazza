/*
** EPITECH PROJECT, 2020
** Client.cpp
** File description:
** Client
*/

#include "../include/Client.hpp"

Client::Client()
{
    
}

Client::Client(int fd)
{
    int rc = 0;

    _pFd = fd;
    _fd = socket(AF_UNIX, SOCK_STREAM, 0);
    //std::cout << "fd client --> " <<_fd << std::endl;
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
    rc = connect(_fd, (struct sockaddr *)&_addr, SUN_LEN(&_addr));
    if (rc < 0)
    {
        perror("connect() failed");
        return;
    }
    //std::cout << _pFd << " " << _fd << std::endl;
    //write(_fd, "Salut salut\n", 13);
}

Client::Client(const Client &c) : _fd(c._fd), _pFd(c._pFd)
{
    _sockAdr = c._sockAdr;
    _sock = c._sock;
    _addr = c._addr;
    _sock_size = c._sock_size;
}

Client &Client::operator=(const Client &c)
{
    _fd = c._fd;
    _pFd = c._pFd;
    _sockAdr = c._sockAdr;
    _sock = c._sock;
    _addr = c._addr;
    _sock_size = c._sock_size;
    return *this;
}

Client::~Client()
{

}

message_t *Client::getMessage()
{
    long x = 0;
    message_t *tmp = new message_t;
    x = read(_fd, tmp, sizeof(message_t));
    if (x < 0) {
        perror("read failed");
        return NULL;
    }
    if (tmp->cmd == 2) {
        //std::cout << "On envoi la struct" << std::endl;
        tmp->cmd = 4;
        tmp->response = 5;
        Client::send(tmp);
    }
    return tmp;
}

void Client::send(message_t *data)
{
    write(_fd, data, sizeof(*data));
}

int Client::getFD()
{
    return _fd;
}