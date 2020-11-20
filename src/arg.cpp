/*
** EPITECH PROJECT, 2020
** arg.cpp
** File description:
** arg
*/

#include "../include/my.hpp"

int check_if_n(char *str, int version)
{
    for (int i = 0; str[i] != 0; i++) {
        if (version == 0 && (str[i] < 48 || str[i] > 57))
            return (84);
        if (version == 1 && \
        (str[i] == 47 || (str[i] < 46 || str[i] > 57)))
            return (84);
    }
    return (0);
}

int check_arg(int ac, char **av)
{
    if (ac != 4)
        return (84);
    if (check_if_n(av[1], 1) != 0 || check_if_n(av[2], 0) != 0 \
    || check_if_n(av[3], 0) != 0)
        return (84);
    return (0);
}