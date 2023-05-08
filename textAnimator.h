#pragma once
// I don't know what I am doing
// All I know is all of this code will be added at the start of the main.cpp when compiled


#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>


void print_animated(std::string text, float seconds)
{
    int length = text.length(); // Get length of the text.
    if (length < 1) // No text, no print.
    {
        return;
    }
    int waitTime = (int) ((seconds * 1000.0) / ((float) length)) + 1; // Calculate the time interval between each letter to print.
    for (int i; i < length; i++) // Iterate over the string.
    {
        std::cout << text[i]; // Print the char.
        std::this_thread::sleep_for(std::chrono::milliseconds(waitTime)); // Wait
    }
    std::cout << "\n"; // End line
}