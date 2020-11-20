/*
** EPITECH PROJECT, 2020
** Param.hpp
** File description:
** Param
*/

#ifndef PARAM_HPP_
#define PARAM_HPP_

#include <iostream>

class Param {
    public:
        Param();
        Param(char **av);
        ~Param();

    //Getter
        double getCtime();
        int getNcook();
        int getTimer();
    //Setter
    protected:
    private:
        double _cTime;
        int _nCook;
        int _timer;
};

#endif /* !PARAM_HPP_ */
