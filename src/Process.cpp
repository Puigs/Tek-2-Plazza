/*
** EPITECH PROJECT, 2020
** Process.cpp
** File description:
** Process
*/

#include "../include/Process.hpp"

Process::Process(Kitchen &kitchen) : _state(STARTED)
{
    _status = 0;
    _pid = fork();

    if (_pid == 0) {
        kitchen.start();
        exit(0);
    } else if (_pid == -1) {
        _state = FAILED;
    } else {
        _state = RUNNING;
    }
}

Process::~Process()
{
    waitpid(_pid, &_status, 0);
    if (WIFSIGNALED(_status)) {
        std::cerr << "Error while closing kitchen!" << std::endl;
    } else if (WEXITSTATUS(_status)) {
        _state = DEAD;
        std::cout << "Kitchen closed successfully!" << std::endl;
    }
}