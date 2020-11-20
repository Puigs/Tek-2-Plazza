/*
** EPITECH PROJECT, 2020
** Error.cpp
** File description:
** Error
*/

#include "../include/Error.hpp"

Error::Error()
{
}

Error::~Error()
{
}

/*Error::Error(const Error &error) 
{
    
}

void Error::operator=(const Error &error)
{
    
}*/

std::vector<std::string> Error::call_arg(std::vector<std::string> cmd)
{
    for (size_t y = 0; y < cmd.size(); y++) {
        for (size_t i = 0; i < cmd[y].size(); i++) {
        if (cmd[y][i] == ' ') {
            cmd[y].erase(0, 1);        
            i--;
        } else
            break;
    }
        for (size_t i = cmd[y].size(); i > 0; i--) {
            if (cmd[y][i] == ' ') {
                cmd[y].pop_back();
            } else
                break;
        }
        try {
            check_arg(cmd[y]);
        } catch (std::invalid_argument e) {
            std::cout << e.what() << std::endl;
            cmd.clear();
        }
    }
    return cmd;
}

    
void Error::check_arg(std::string cmd)
{
    std::istringstream iss(cmd);
    std::vector<std::string> ret((std::istream_iterator<std::string>(iss)), \
    std::istream_iterator<std::string>());
    if (ret.size() < 3)
        throw std::invalid_argument(cmd + " = " + "Too less argument");
    else if (ret.size() > 3)
        throw std::invalid_argument(cmd + " = " + "Too much argument");
    check_type(ret[0]);
    check_size(ret[1]);
    check_number(ret[2]);
}

void Error::check_type(std::string type)
{
    std::vector<std::string> tmp = {"Regina", "Margarita", "Americana", "Fantasia"};
    for (size_t y = 0; y < tmp.size(); y++)
        if (type == tmp[y])
            return;
    throw std::invalid_argument(type + " = " + "Wrong type");
}

void Error::check_size(std::string size)
{
    std::vector<std::string> tmp = {"S", "M", "L", "XL", "XXL"};
    for (size_t y = 0; y < tmp.size(); y++)
        if (size == tmp[y])
            return;
    throw std::invalid_argument(size + " = " + "Wrong size");
}

void Error::check_number(std::string number)
{
    int check = 0;

    if (number[0] != 'x' || number.size() == 1)
        throw std::invalid_argument(number + " = " + "Problem with number of pizza");
    for (size_t i = 1; i < number.size(); i++) {
        if (number[i] < 48 || number[i] > 57)
            throw std::invalid_argument(number + " = " + "Problem with number of pizza");
        if (number[i] != '0')
            check = 1;
    }
    if (check == 0)
        throw std::invalid_argument(number + " = " + "You need to command at least one pizza");
}