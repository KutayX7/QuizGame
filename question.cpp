#include <iostream>
#include <string>
#include <fstream>
#include "textAnimator.h"
#include "question.h"

Question::Question() = default;

void Question::printq()
{
    std::cout << " ( Question : #" << index << " ) ";
    int length = question.length();
    std::string *words = new std::string[length];
    int l = 0, w = 0;
    for (int i = 0; i < length; i++)
    {
        char c = question[i];
        if (c == ' ')
        {
            print_animated(words[w] + " ", 0.5);
            w += 1;
        }
        else
        {
            words[w] += c;
        }
        l += 1;
        if (l > 32)
        {
            std::cout << "\n";
            l = 0;
        }
    }
    std::cout << "\n";
    print_animated(" 1) " + options[0] + "\n", 0.5);
    print_animated(" 2) " + options[1] + "\n", 0.5);
    print_animated(" 3) " + options[2] + "\n", 0.5);
    print_animated(" 4) " + options[3] + "\n", 0.5);
    delete[] words;
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