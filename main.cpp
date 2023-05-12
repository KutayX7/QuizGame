#include <iostream>
#include <string>
#include <cstdlib>
#include "textAnimator.h"
#include "interactions.h"
#include "question.h"

using namespace std;

int main()
{
    print_animated("Welcome to The Quiz Game! \n", 1.0);
    Question q1;
    q1.question = "Test question 1";
    q1.id = 0;
    q1.index = 1;
    string options[] = {" Option 1 ( | )"," Option 2 (\\|/)"," Option 3 (This one is correct)"," Option 4 (Absolutely incorrect)"};
    q1.options[0] = options[0];
    q1.options[1] = options[1];
    q1.options[2] = options[2];
    q1.options[3] = options[3];
    q1.correct_option = 3 - 1;
    q1.printq();
    string input = get_input_from_user_with_timeout(10);
    if (input == "")
    {
        cout << "\n Time's up! You're a failure!";
    }
    else if (input == q1.options[q1.correct_option])
    {
        cout << "\n Correct!";
    }
    else
    {
        cout << "\n Incorrect! You're a menace to the society!";
    }
    return 0;
}