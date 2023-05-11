#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <time.h>
#include "textAnimator.h"

using namespace std;

typedef chrono::duration<int> seconds_type;

bool isWaitingForInput = false;
string cachedInput;

chrono::time_point timeoutTime = chrono::high_resolution_clock().now();

void userInputTimeout() // Not fully implemented yet
{
    cout << "\n Time's up! \n";
}

string getUserInput()
{
    if (isWaitingForInput) // Check for race conditions
    {
        while (isWaitingForInput)
        {
            cout.flush();
        }
        return cachedInput;
    }
    isWaitingForInput = true;
    string input;
    cin >> input;
    cachedInput = input; // Store the input from the user
    isWaitingForInput = false;
    return input;
}


string getTimedUserInput(int seconds)
{
    if (isWaitingForInput) // Check for race conditions
    {
        while (isWaitingForInput)
        {
            cout.flush();
            if (chrono::high_resolution_clock().now() > timeoutTime)
            {
                userInputTimeout();
                break;
            }
        }
        if (cachedInput == "")
        {
            userInputTimeout();
        }
        return cachedInput;
    }
    else
    {
        cachedInput = "";
        thread inputThread (getUserInput);
        seconds_type Duration (seconds);
        timeoutTime = chrono::high_resolution_clock().now() + Duration;
        inputThread.detach();
        while (!isWaitingForInput)
        {
            cout.flush();
        }
        while (isWaitingForInput)
        {
            cout.flush();
            if (chrono::high_resolution_clock().now() > timeoutTime)
            {
                userInputTimeout();
                break;
            }
        }
        return cachedInput;
    }
}   


int main()
{
    print_animated("Welcome to The Quiz Game!", 2.0);
    print_animated("Please type \"something\" in 10 seconds.", 2.0); // Just for testing
    string input = getTimedUserInput(10);
    if (input.compare("") != 0)
    {
        if (input.compare("something") == 0)
        {
            cout << "Correct";
        }
        else
        {
            cout << "Fail";
        }
    }
    return 0;
}