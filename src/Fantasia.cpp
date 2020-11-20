/*
** EPITECH PROJECT, 2020
** Fantasia.cpp
** File description:
** Fantasia
*/

#include "../include/Fantasia.hpp"

Fantasia::Fantasia(Pizza::PizzaSize size, double bakingTime)
: Pizza(Pizza::Fantasia, size, bakingTime)
{
    _ingredients.push_back(Pizza::Tomato);
    _ingredients.push_back(Pizza::Eggplant);
    _ingredients.push_back(Pizza::GoatCheese);
    _ingredients.push_back(Pizza::ChiefLove);
    _bakingTime = static_cast<u_int32_t>((4.0 * 1000) * bakingTime);
}

Fantasia::~Fantasia()
{
}
