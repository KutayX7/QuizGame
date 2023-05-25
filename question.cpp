#include <iostream>
#include <string>
#include <fstream>
#include "textAnimator.h"
#include "question.h"
#include "interactions.h"

Question::Question()
{
    id = 0;
    index = 1;
}

void Question::printq()
{
    clear_screen();
    std::cout << "\033[1;36m ( Question : #" << index << " ) ";
    int length = question.length();
    print_animated(question, ((float) length) * 0.05);
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

bool Question::prompt(float timeout)
{
    printq();
    std::string input = get_input_from_user_with_timeout(timeout);
    bool correct = check(input);
    if (correct)
    {
        std::cout << "\033[1;32mCorrect!\033[0m\n";
        std::cout << "Description: ";
        print_animated(description + "\n", 0.75);
        enter_to_continue();
    }
    else
    {
        std::cout << "\033[1;31mInCorrect!\033[0m\n";
        std::cout << "Description: ";
        print_animated(description + "\n", 3.0);
        enter_to_continue();
    }
    return correct;
}

bool Question::operator<(Question other)
{
    return index < other.index;
}
bool Question::operator>(Question other)
{
    return index > other.index;
}