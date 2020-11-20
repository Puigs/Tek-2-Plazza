/*
** EPITECH PROJECT, 2020
** Process.hpp
** File description:
** Process
*/

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "Kitchen.hpp"

class Process {
    enum state {
        FAILED = -1,
        STARTED,
        RUNNING,
        DEAD
    };

    public:
        Process(Kitchen &kitchen);
        ~Process();
    protected:
    private:
        int _pid;
        int _status;
        state _state;
};

#endif /* !PROCESS_HPP_ */
