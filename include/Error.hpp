/*
** EPITECH PROJECT, 2020
** Error.hpp
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iterator>
#include <sstream>

class Error : public std::exception {
    public:
        Error();
       // Error(const Error &error);
        ~Error();
        //void operator=(const Error &error);
        std::vector<std::string> call_arg(std::vector<std::string> cmd);
        void check_arg(std::string cmd);
        void check_type(std::string type);
        void check_size(std::string size);
        void check_number(std::string number);
    protected:
    private:
};

#endif /* !ERROR_HPP_ */
