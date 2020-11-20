/*
** EPITECH PROJECT, 2020
** Fantasia.hpp
** File description:
** Fantasia
*/

#ifndef FANTASIA_HPP_
#define FANTASIA_HPP_

#include "Pizza.hpp"

class Fantasia : public Pizza {
    public:
        Fantasia(Pizza::PizzaSize size, double bakingTime);
        ~Fantasia();
    protected:
    private:
};

#endif /* !FANTASIA_HPP_ */
