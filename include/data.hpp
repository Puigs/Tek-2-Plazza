/*
** EPITECH PROJECT, 2020
** data.hpp
** File description:
** data
*/

#ifndef DATA_HPP_
#define DATA_HPP_

#include "Pizza.hpp"

typedef struct test_s 
{
    int y;
} test_t;

typedef struct data_s {
    int status;
    int fd;
    std::string buffer;
    message_t *data;
} data_t;

#endif /* !DATA_HPP_ */
