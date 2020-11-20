/*
** EPITECH PROJECT, 2020
** PizzaFactory.hpp
** File description:
** PizzaFactory
*/

#ifndef PIZZAFACTORY_HPP_
#define PIZZAFACTORY_HPP_

#include "Margarita.hpp"
#include "Regina.hpp"
#include "Americana.hpp"
#include "Fantasia.hpp"
#include <string>
#include <map>

class PizzaFactory {
    public:
        PizzaFactory();
        ~PizzaFactory();
        Pizza *makePizza(std::string type, std::string size, double bakingMultiplier);
    protected:
    private:
        std::map<std::string, Pizza::PizzaType> _types;
        std::map<std::string, Pizza::PizzaSize> _sizes;
};

#endif /* !PIZZAFACTORY_HPP_ */
