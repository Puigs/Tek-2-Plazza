/*
** EPITECH PROJECT, 2020
** PizzaFactory.cpp
** File description:
** PizzaFactory
*/

#include "../include/PizzaFactory.hpp"

PizzaFactory::PizzaFactory()
{
    _types["Regina"] = Pizza::PizzaType::Regina;
    _types["Margarita"] = Pizza::PizzaType::Margarita;
    _types["Americana"] = Pizza::PizzaType::Americana;
    _types["Fantasia"] = Pizza::PizzaType::Fantasia;
    _sizes["S"] = Pizza::PizzaSize::S;
    _sizes["M"] = Pizza::PizzaSize::M;
    _sizes["L"] = Pizza::PizzaSize::L;
    _sizes["XL"] = Pizza::PizzaSize::XL;
    _sizes["XXL"] = Pizza::PizzaSize::XXL;
}

PizzaFactory::~PizzaFactory()
{
}

Pizza *PizzaFactory::makePizza(std::string type, std::string size, double bakingMultiplier)
{
    Pizza::PizzaType pizzaType = _types[type];

    switch (pizzaType)
    {
    case Pizza::Regina:
        return new Regina(_sizes[size], bakingMultiplier);
    case Pizza::Margarita:
        return new Margarita(_sizes[size], bakingMultiplier);
    case Pizza::Americana:
        return new Americana(_sizes[size], bakingMultiplier);
    case Pizza::Fantasia:
        return new Fantasia(_sizes[size], bakingMultiplier);
    default:
        return nullptr;
    }
}