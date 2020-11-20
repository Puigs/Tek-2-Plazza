/*
** EPITECH PROJECT, 2020
** Margarita.hpp
** File description:
** Margarita
*/

#ifndef MARGARITA_HPP_
#define MARGARITA_HPP_

#include "Pizza.hpp"

class Margarita : public Pizza {
    public:
        Margarita(Pizza::PizzaSize size, double bakingTime);
        ~Margarita();
    protected:
    private:
};

#endif /* !MARGARITA_HPP_ */
