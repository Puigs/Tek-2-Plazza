/*
** EPITECH PROJECT, 2020
** Regina.hpp
** File description:
** Regina
*/

#ifndef REGINA_HPP_
#define REGINA_HPP_

#include "Pizza.hpp"

class Regina : public Pizza {
    public:
        Regina(Pizza::PizzaSize size, double bakingTime);
        ~Regina();
    protected:
    private:
};

#endif /* !REGINA_HPP_ */
