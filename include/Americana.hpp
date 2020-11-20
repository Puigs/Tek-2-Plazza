/*
** EPITECH PROJECT, 2020
** Americana.hpp
** File description:
** Americana
*/

#ifndef AMERICANA_HPP_
#define AMERICANA_HPP_

#include "Pizza.hpp"

class Americana : public Pizza {
    public:
        Americana(Pizza::PizzaSize size, double bakingTime);
        ~Americana();
    protected:
    private:
};

#endif /* !AMERICANA_HPP_ */
