#pragma once

#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

class User
{
    public:
        std::string name;
        int score;
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

class Settings
{
    public:
        std::unordered_map<std::string, bool> map;
        Settings();
        ~Settings() = default;
        bool set(std::string setting, bool value = true);
        bool get(std::string setting);
        std::string get_str(std::string setting);
        bool toggle(std::string setting);
};