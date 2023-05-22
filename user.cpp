#include <iostream>
#include <string>
#include "user.h"

User::User(std::string _name, int _score)
{
    name = _name;
    score = _score;
}

std::string User::serialize()
{
    std::string scoreStr = std::to_string(score);
    return name + "\n" + scoreStr + "\n";
}