/*
** EPITECH PROJECT, 2020
** Param.cpp
** File description:
** Param
*/

#include "../include/Param.hpp"

Param::Param()
{
    
}

Param::Param(char **av)
{
    _cTime = std::stod(av[1]);
    _nCook = atoi(av[2]);
    _timer = atoi(av[3]);
}

Param::~Param()
{
}

double Param::getCtime()
{
    return _cTime;
}

int Param::getNcook()
{
    return _nCook;
}

int Param::getTimer()
{
    return _timer;
}