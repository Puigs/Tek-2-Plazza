/*
** EPITECH PROJECT, 2020
** Parser.cpp
** File description:
** Parser
*/

#include "../include/Parser.hpp"

Parser::Parser()
{
    
}

Parser::Parser(double timer)
{
    _timer = timer;
    _tmp["Regina"] = Pizza::PizzaType::Regina;
    _tmp["Margarita"] = Pizza::PizzaType::Margarita;
    _tmp["Americana"] = Pizza::PizzaType::Americana;
    _tmp["Regina"] = Pizza::PizzaType::Regina;
    _tmp2["S"] = Pizza::PizzaSize::S;
    _tmp2["M"] = Pizza::PizzaSize::M;
    _tmp2["L"] = Pizza::PizzaSize::L;
    _tmp2["XL"] = Pizza::PizzaSize::XL;
    _tmp2["XXL"] = Pizza::PizzaSize::XXL;
}

Parser::~Parser()
{
}

/*Parser::Parser(const Parser &parser) 
{

}

void Parser::operator=(const Parser &parser)
{

}*/

void Parser::setCmd(std::string str)
{
    std::string tmp;

    if (!_array.empty())
        _array.clear();
    if (!_cmd.empty())
        _cmd.clear();
    _cmd.push_back(tmp);
    for (size_t i = 0, x = 0, y = 0; i < str.size(); i++, x++) {
        if (str[i] == ';') {
            _cmd.push_back(tmp);
            y++;
            x = -1;
            continue;
        }
        _cmd[y] += str[i];
    }
    _cmd = _error.call_arg(_cmd);
    if (_cmd.empty())
        return;
    create_Pizza();
}

std::vector<message_t *> Parser::getCmd()
{
    return _array;
}

void Parser::create_Pizza()
{
    PizzaFactory pizza;

    for (size_t i = 0; i < _cmd.size(); i++) {
        std::istringstream iss(_cmd[i]);
        std::vector<std::string> ret((std::istream_iterator<std::string>(iss)), \
        std::istream_iterator<std::string>());
        
        Pizza *tmp = pizza.makePizza(ret[0], ret[1], _timer);
        if (tmp == NULL)
            std::cout << "Problème\n" << std::endl;
        ret[2][0] = '0';
        int nb = std::stoi(ret[2]);
        for (int i = 0; i < nb; i++)
            _array.push_back(Pizza::pack(*tmp));
    }
}