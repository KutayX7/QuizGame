#include <iostream>
#include <string>
#include <thread>
#include <time.h>

typedef std::chrono::duration<int> seconds_type;

bool isWaitingForInput = false;
std::string cachedInput;

std::chrono::time_point<std::chrono::system_clock> timeoutTime;

void userInputTimeout() // Not fully implemented yet
{
    std::cout << "\n : Time's up! : \n";
}

std::string get_input_from_user()
{
    if (isWaitingForInput) // Check for race conditions
    {
        while (isWaitingForInput)
        {
            std::cout.flush();
        }
        return cachedInput;
    }
    isWaitingForInput = true;
    std::string input;
    std::cin >> input;
    std::cin.ignore();
    cachedInput = input; // Store the input from the user
    isWaitingForInput = false;
    return input;
}


std::string get_input_from_user_with_timeout(int seconds)
{
    if (isWaitingForInput) // Check for race conditions
    {
        while (isWaitingForInput)
        {
            std::cout.flush();
            if (std::chrono::system_clock().now() > timeoutTime)
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
        std::thread inputThread (get_input_from_user);
        seconds_type Duration (seconds);
        timeoutTime = std::chrono::system_clock().now() + Duration;
        inputThread.detach();
        while (!isWaitingForInput)
        {
            std::cout.flush();
        }
        while (isWaitingForInput)
        {
            std::cout.flush();
            if (std::chrono::system_clock().now() > timeoutTime)
            {
                userInputTimeout();
                break;
            }
        }
        return cachedInput;
    }
}

void clear_screen(int width, int height)
{
    std::string line = "";
    for (int x = 0; x < width; x++)
    {
        line = line + " ";
    }
    line = line + "\n";
    std::string out = "\033[0;0H";
    for (int y = 0; y < height; y++)
    {
        out = out + line;
    }
    out = out + "\033[0;0H";
    std::cout << out;
    std::cout.flush();
}

void enter_to_continue()
{
    if (isWaitingForInput) // Check for race conditions
    {
        std::cout << " Please type \"\033[1;33mcontinue\033[0m\" to continue...\n";
        std::cout.flush();
        while (isWaitingForInput)
        {
            std::cout.flush();
        }
        return;
    }
    std::cout << "Press ENTER to continue...";
    std::cout.flush();
    isWaitingForInput = true;
    std::cin.ignore();
    isWaitingForInput = false;
}