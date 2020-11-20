/*
** EPITECH PROJECT, 2020
** Pizza.hpp
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <map>

enum Command {
    bake,
    canBake,
    closeKitchen,
    inactiveCooksNb,
    status
};

class Pizza {
    public:
        enum PizzaType {
            Regina = 1,
            Margarita = 2,
            Americana = 4,
            Fantasia = 8
        };

        enum PizzaSize {
            S = 1,
            M = 2,
            L = 4,
            XL = 8,
            XXL = 16
        };

        enum Ingredients {
            Tomato = 1,
            Gruyere = 2,
            Ham = 4,
            Mushroom = 8,
            Steak = 16,
            Eggplant = 32,
            GoatCheese = 64,
            ChiefLove = 128,
            Doe = 256
        };

        Pizza();
        Pizza(PizzaType type, PizzaSize size, double bakingTime);
        Pizza(const Pizza &pizza);
        void operator=(const Pizza &rhs);
        ~Pizza();
        static struct message_s *pack(Pizza pizza);
        static Pizza *unpack(struct message_s *data);
        std::vector<Ingredients> getIngredients() const;
        PizzaType getType() const;
        PizzaSize getSize() const;
        u_int32_t getBakingTime() const;
        double getBakingMultiplier() const;
    protected:
        std::vector<Ingredients> _ingredients;
        PizzaType _type;
        PizzaSize _size;
        double _bakingMultiplier;
        u_int32_t _bakingTime;
    private:
};

typedef struct message_s {
    u_int32_t magic = 0x42424242;
    u_int32_t cmd;
    u_int32_t response;
    u_int32_t pizzaSize;
    u_int32_t pizzaType;
    double bakingMultiplier;
} message_t;

#endif /* !PIZZA_HPP_ */
