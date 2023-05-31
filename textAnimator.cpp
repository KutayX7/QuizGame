#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include "textAnimator.h"

// Waits for given seconds.
// Not very accurate!
void wait(double seconds)
{
    int ms = (int) (seconds * ((double) 1000.0));
    std::this_thread::sleep_for(std::chrono::milliseconds(ms)); // Wait
}

// Very fast queued printing of individual characters.
// Edga-cases are currently unknown.
void print_char(char c, double delay, int position, int* counter)
{
    wait(delay);
    while (*counter != position)
    {
        std::cout.flush();
    }
    std::cout << c;
    std::cout.flush();
    *counter += 1;
}

// Prints the given string in the given time limit.
// Probably not thread safe. Don't call this outside of the main thread!
void print_animated(std::string text, double seconds)
{
    seconds = (double) seconds;
    int length = text.length(); // Get length of the text.
    if (length < 1) // No text, no print.
    {
        return;
    }
    int counter = 0;
    int* counter_ptr = &counter;
    double waitTime = (seconds / ((double) length)) + 0.000001; // Calculate the time interval between each letter to print.
    for (int i = 0; i < length; i++) // Iterate over the string. Schedules characters to print.
    {
        std::thread print_thread (print_char, text[i], waitTime * i, i, counter_ptr);
        print_thread.detach();
    }
    while (counter < length)
    {
        std::cout.flush(); // A bit inefficient but accurate way of waiting.
    }
}