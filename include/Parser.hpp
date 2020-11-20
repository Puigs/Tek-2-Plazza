/*
** EPITECH PROJECT, 2020
** Parser.hpp
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <vector>
#include "Error.hpp"
#include "PizzaFactory.hpp"
#include <map>

class Parser {
    public:
        Parser();
        Parser(double timer);
        ~Parser();
        //Parser(const Parser &parser);
        //void operator=(const Parser &parser);
        void setCmd(std::string);
        std::vector<message_t *> getCmd();
        void create_Pizza();
    protected:
    private:
        double _timer;
        std::vector<std::string> _cmd;
        std::vector<std::string> _ret;
        Error _error;
        std::vector<message_t *> _array;
        std::map<std::string, Pizza::PizzaType> _tmp;
        std::map<std::string, Pizza::PizzaSize> _tmp2;
};

#endif /* !PARSER_HPP_ */
