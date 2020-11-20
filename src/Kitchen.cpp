/*
** EPITECH PROJECT, 2020
** Kitchen.cpp
** File description:
** Kitchen
*/

#include "../include/Kitchen.hpp"

Kitchen::Kitchen(u_int32_t fd, u_int32_t cookNb, u_int32_t stockMultiplier)
: _fd(fd), _cookNb(cookNb), _stockMultiplier(stockMultiplier), _kitchenLifeTime(5), _dead(false)
{
    _cooks = new ThreadPool(cookNb, 7500);
    _stocks = new SafeMap<Pizza::Ingredients>(7500);
    _comm = new Client(fd);
    _stocks->push(Pizza::Tomato, 5);
    _stocks->push(Pizza::Gruyere, 5);
    _stocks->push(Pizza::Ham, 5);
    _stocks->push(Pizza::Mushroom, 5);
    _stocks->push(Pizza::Steak, 5);
    _stocks->push(Pizza::GoatCheese, 5);
    _stocks->push(Pizza::ChiefLove, 5);
    _stocks->push(Pizza::Eggplant, 5);
    _stocks->push(Pizza::Doe, 5);

    _commandsActions[Command::bake] = &Kitchen::bakePizza;
    _commandsActions[Command::canBake] = &Kitchen::canBakePizza;
    _commandsActions[Command::closeKitchen] = &Kitchen::closeKitchen;
    _commandsActions[Command::inactiveCooksNb] = &Kitchen::getInactiveCooksNb;
    _commandsActions[Command::status] = &Kitchen::kitchenStatus;
}

Kitchen::~Kitchen()
{
    if (_cooks)
        delete _cooks;
    if (_stocks)
        delete _stocks;
    if (_comm)
        delete _comm;
}

void Kitchen::refillStocks()
{
    std::mutex lock;
    std::mutex printLock;

    while (_dead == false) {
        std::this_thread::sleep_for(std::chrono::milliseconds(_stockMultiplier));
        if (_dead == false) {
            for (std::size_t ingredient = 1; ingredient != 512; ingredient *= 2) {
                _stocks->inc(static_cast<Pizza::Ingredients>(ingredient));
            }
        }
    }
}

void Kitchen::checkActivity()
{
    std::mutex printLock;
    _activityClock = std::chrono::high_resolution_clock::now();
    auto t_end = std::chrono::high_resolution_clock::now();
    message_t *message = new message_t();
    
    message->cmd = Command::closeKitchen;
    message->response = true;
    while (_dead == false) {
        if (_cooks->getActive() != 0)
            _activityClock = std::chrono::high_resolution_clock::now();
        t_end = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration<double, std::milli>(t_end - _activityClock).count() > _kitchenLifeTime * 1000) {
            _dead = true;
            _comm->send(message);
        }
    }
}

void Kitchen::bakePizza(message_t *message)
{
    Pizza *pizza = Pizza::unpack(message);

    _cooks->addTask(&ThreadPool::cook, _cooks, _stocks, &_dead);
    _cooks->addCmd(*pizza);
}

void Kitchen::canBakePizza(message_t *message)
{
    if (_cooks->getWaitingCmdSize() == _cookNb) {
        message->response = false;
        _comm->send(message);
    } else {
        message->response = true;
        _comm->send(message);
    }
}

void Kitchen::getInactiveCooksNb(message_t *message)
{
    u_int32_t inactiveCooks = _cookNb - _cooks->getActive();
    message->response = inactiveCooks;
    _comm->send(message);
}

void Kitchen::closeKitchen(message_t *message)
{
    std::mutex printLock;

    _dead = true;
    {
        std::unique_lock<std::mutex> L(printLock);
        std::cout << "Closing Kitchen." << std::endl;
    }
    message->response = true;
    _comm->send(message);
}

void Kitchen::kitchenStatus(message_t *message)
{   
    static std::map<Pizza::Ingredients, std::string> ingredientsToString;
    std::mutex printLock;

        ingredientsToString[Pizza::Tomato] = "Tomato";
        ingredientsToString[Pizza::Gruyere] = "Gruyere";
        ingredientsToString[Pizza::Ham] = "Ham";
        ingredientsToString[Pizza::Mushroom] = "Mushroom";
        ingredientsToString[Pizza::Steak] = "Steak";
        ingredientsToString[Pizza::Eggplant] = "Eggplant";
        ingredientsToString[Pizza::GoatCheese] = "GoatCheese";
        ingredientsToString[Pizza::ChiefLove] = "ChiefLove";
        ingredientsToString[Pizza::Doe] = "Doe";

    {
        std::unique_lock<std::mutex> L(printLock);
        std::cout << "Stocks in the thread number:" << getpid() << std::endl;
        for (std::size_t ingredient = 1; ingredient != 512; ingredient *= 2) {
            std::cout << "[" << ingredientsToString[static_cast<Pizza::Ingredients>(ingredient)] << "]=[" << 
            _stocks->at(static_cast<Pizza::Ingredients>(ingredient)) << "] ";
        }
        std::cout << std::endl;
        std::cout << "There is " << _cooks->getActive() << " cooks working!" << std::endl;
    }
    _comm->send(message);
}

void Kitchen::parseCommands(message_t *command)
{
    if (_dead == false && command != nullptr) {
        if (_commandsActions.find(static_cast<Command>(command->cmd)) != _commandsActions.end())
            (this->*(_commandsActions.at(static_cast<Command>(command->cmd))))(command);
    }
}

void Kitchen::start()
{
    message_t *message;

    MyThread stockThread;
    stockThread.newLambda(&Kitchen::refillStocks, this);

    MyThread activityThread;
    activityThread.newLambda(&Kitchen::checkActivity, this);
    
    while (_dead == false) {
        message = _comm->getMessage();
        parseCommands(message);
    }
}