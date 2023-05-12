#include <iostream>
#include <string>

class Question
{
public:
    std::string question;
    std::string options[4];
    int correct_option, id, index;
    Question();
    void printq();
};