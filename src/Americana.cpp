/*
** EPITECH PROJECT, 2020
** Americana.cpp
** File description:
** Americana
*/

#include "../include/Americana.hpp"

Americana::Americana(Pizza::PizzaSize size, double bakingTime)
: Pizza(Pizza::Americana, size, bakingTime)
{
    _ingredients.push_back(Pizza::Tomato);
    _ingredients.push_back(Pizza::Gruyere);
    _ingredients.push_back(Pizza::Steak);
    _bakingTime = static_cast<u_int32_t>((2.0 * 1000) * bakingTime);
}

Americana::~Americana()
{
}
