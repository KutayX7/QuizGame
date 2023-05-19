#include <iostream>
#include <string>

class User
{
    public:
        std::string name;
        int score;
        User(std::string _name, int _score);
        std::string serialize();
};