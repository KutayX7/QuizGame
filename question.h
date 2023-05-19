#include <iostream>
#include <string>

class Question
{
public:
    std::string question;
    std::string description;
    std::string options[4];
    int correct_option, id, index;
    Question();
    void printq();
    bool check(int answer);
    bool check(std::string answer);
};