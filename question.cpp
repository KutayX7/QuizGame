#include <iostream>
#include <string>
#include <fstream>
#include "textAnimator.h"
#include "question.h"

Question::Question()
{
    id = 0;
    index = 1;
}

void Question::printq()
{
    std::cout << "\033[1;36m ( Question : #" << index << " ) ";
    int length = question.length();
    print_animated(question, ((float) length) * 0.125);
    std::cout << "\n\033[0m";
    print_animated(" 1) " + options[0] + "\n", 0.5);
    print_animated(" 2) " + options[1] + "\n", 0.5);
    print_animated(" 3) " + options[2] + "\n", 0.5);
    print_animated(" 4) " + options[3] + "\n", 0.5);
}

bool Question::check(int answer)
{
    if ((answer - 1) == correct_option)
    {
        return true;
    }
    return false;
}

bool Question::check(std::string answer)
{
    std::string expected_answer;
    switch (correct_option)
    {
    case 0:
        expected_answer = "1";
        break;
    case 1:
        expected_answer = "2";
        break;
    case 2:
        expected_answer = "3";
        break;
    case 3:
        expected_answer = "4";
        break;
    default:
        break;
    }
    if (answer == expected_answer)
    {
        return true;
    }
    return false;
}

bool Question::operator<(Question other)
{
    return index < other.index;
}
bool Question::operator>(Question other)
{
    return index > other.index;
}