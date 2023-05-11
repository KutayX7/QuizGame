#include <iostream>
#include <string>
#include <cstdlib>
#include "textAnimator.h"
#include "interactions.h"

using namespace std;

int main()
{
    print_animated("Welcome to The Quiz Game!", 1.0);
    print_animated("Please type \"something\" in 10 seconds.", 1.0); // Just for testing
    string input = get_input_from_user_with_timeout(10);
    if (input.compare("") != 0)
    {
        cout << "\n You typed : " << input;
    }
    return 0;
}