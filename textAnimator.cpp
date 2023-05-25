#include "textAnimator.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>

bool _A_THREAD_WAIT_FINISHED = false;

void wait(float seconds) // Avoid using this function directly
{
    _A_THREAD_WAIT_FINISHED = false;
    int ms = (int) (seconds * 1000.0);
    std::this_thread::sleep_for(std::chrono::milliseconds(ms)); // Wait
    _A_THREAD_WAIT_FINISHED = true;
}

void wait_aync(float seconds) // Use this for waiting
{
    std::thread thread_1 (wait, seconds);
    thread_1.detach(); // ASYNC
    while (!_A_THREAD_WAIT_FINISHED)
    {
        std::cout.flush();
    }
    _A_THREAD_WAIT_FINISHED = false;
}

void print_animated(std::string text, float seconds)
{
    int length = text.length(); // Get length of the text.
    if (length < 1) // No text, no print.
    {
        return;
    }
    float waitTime = (seconds / ((float) length)) + 0.001; // Calculate the time interval between each letter to print.
    for (int i; i < length; i++) // Iterate over the string.
    {
        std::cout << text[i]; // Print the char.
        std::cout.flush();
        wait_aync(waitTime);
    }
}