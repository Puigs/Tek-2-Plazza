/*
** EPITECH PROJECT, 2020
** init.cpp
** File description:
** init
*/

#include "../include/my.hpp"

void init_obj(char **av)
{
    Param param(av);
    Parser parser(param.getCtime());

    loop(param, parser);
}