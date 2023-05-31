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
        bool operator<(const User &user2) const;
        bool operator>(const User &user2) const;
        bool operator==(const User user2) const;
};

class LeaderBoard
{
    public:
        std::list<User> users;
        LeaderBoard();
        bool add(User &user);
        bool remove(User &user);
        void print();
};