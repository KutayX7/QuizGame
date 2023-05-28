#pragma once

#include <iostream>
#include <string>
#include <list>

class User
{
    public:
        std::string name;
        int score;
        User();
        User(std::string _name, int _score);
        std::string serialize();
        bool operator<(User &user2);
        bool operator>(User &user2);
};

class LeaderBoard
{
    public:
        std::list<User> users;
        LeaderBoard();
        ~LeaderBoard() = default;
        bool add(User &user);
        bool remove(User &user);
        void print();
};