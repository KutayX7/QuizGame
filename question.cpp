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