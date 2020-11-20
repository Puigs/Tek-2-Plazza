/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** main
*/

#include "include/my.hpp"

int main(int ac, char **av)
{
    if (check_arg(ac, av) != 0) 
        return (84);
    unlink("Server");
    init_obj(av);
    return (0);
}