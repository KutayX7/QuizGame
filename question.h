#pragma once

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
    void printq(double speed = 1);
    bool check(int answer);
    bool check(std::string answer);
    bool prompt(float timeout = 10.0, bool debug_mode = false);
    bool operator<(Question other);
    bool operator>(Question other);
};