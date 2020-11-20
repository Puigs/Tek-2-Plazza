/*
** EPITECH PROJECT, 2020
** Margarita.cpp
** File description:
** Margarita
*/

#include "../include/Margarita.hpp"

Margarita::Margarita(Pizza::PizzaSize size, double bakingTime) 
: Pizza(Pizza::Margarita, size, bakingTime)
{
    _ingredients.push_back(Pizza::Tomato);
    _ingredients.push_back(Pizza::Gruyere);
    _bakingTime = static_cast<u_int32_t>((1.0 * 1000) * bakingTime);
}

Margarita::~Margarita()
{
}
