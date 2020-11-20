/*
** EPITECH PROJECT, 2020
** Pizza.cpp
** File description:
** Pizza
*/

#include "../include/Pizza.hpp"
#include "../include/PizzaFactory.hpp"

Pizza::Pizza()
{
    this->_type = Pizza::Regina;
    this->_size = S;
    this->_bakingTime = _bakingTime;
    this->_ingredients.push_back(Pizza::Doe);
}

Pizza::Pizza(PizzaType type, PizzaSize size, double bakingTime)
{
    this->_type = type;
    this->_size = size;
    this->_bakingMultiplier = bakingTime;
    this->_ingredients.push_back(Pizza::Doe);
}

Pizza::~Pizza()
{
}

Pizza::Pizza(const Pizza &pizza)
{
    _type = pizza._type;
    _size = pizza._size;
    _bakingTime = pizza._bakingTime;
    _bakingMultiplier = pizza._bakingMultiplier;
    _ingredients = pizza._ingredients;
}

void Pizza::operator=(const Pizza &rhs)
{
    this->_type = rhs.getType();
    this->_size = rhs.getSize();
    this->_bakingTime = rhs.getBakingTime();
    this->_bakingMultiplier = rhs.getBakingMultiplier();
    this->_ingredients = std::vector<Ingredients>();
    if (!rhs.getIngredients().empty())
        _ingredients = rhs.getIngredients();
}

std::vector<Pizza::Ingredients> Pizza::getIngredients() const
{
    return this->_ingredients;
}

Pizza::PizzaType Pizza::getType() const
{
    return this->_type;
}

Pizza::PizzaSize Pizza::getSize() const
{
    return this->_size;
}

u_int32_t Pizza::getBakingTime() const
{
    return this->_bakingTime;
}

double Pizza::getBakingMultiplier() const
{
    return this->_bakingMultiplier;
}

struct message_s *Pizza::pack(Pizza pizza)
{
    message_t *cmd = (message_t *) malloc(sizeof(message_t));

    cmd->cmd = Command::bake;
    cmd->response = 0;
    cmd->pizzaSize = pizza.getSize();
    cmd->pizzaType = pizza.getType();
    cmd->bakingMultiplier = pizza.getBakingMultiplier();
    return cmd;
}

Pizza *Pizza::unpack(struct message_s *data)
{
    std::map<PizzaType, std::string> types = {
        {Pizza::Regina, "Regina"},
        {Pizza::Americana, "Americana"},
        {Pizza::Fantasia, "Fantasia"},
        {Pizza::Margarita, "Margarita"}
    };
    std::map<PizzaSize, std::string> sizes = {
        {Pizza::S, "S"},
        {Pizza::M, "M"},
        {Pizza::L, "L"},
        {Pizza::XL, "XL"},
        {Pizza::XXL, "XXL"}
    };
    PizzaFactory pf;

    return pf.makePizza(types[static_cast<PizzaType>(data->pizzaType)], sizes[static_cast<PizzaSize>(data->pizzaSize)], data->bakingMultiplier);
}