/*
** EPITECH PROJECT, 2020
** Regina.cpp
** File description:
** Regina
*/

#include "../include/Regina.hpp"

Regina::Regina(Pizza::PizzaSize size, double bakingTime)
: Pizza(Pizza::Regina, size, bakingTime)
{
    _ingredients.push_back(Pizza::Tomato);
    _ingredients.push_back(Pizza::Gruyere);
    _ingredients.push_back(Pizza::Ham);
    _ingredients.push_back(Pizza::Mushroom);
    _bakingTime = static_cast<u_int32_t>((2.0 * 1000) * bakingTime);
}

Regina::~Regina()
{
}
