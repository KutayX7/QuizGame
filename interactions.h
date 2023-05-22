#pragma once

#include <iostream>
#include <string>

void clear_screen(int width = 128, int height = 256);
void enter_to_continue();
std::string get_input_from_user();
std::string get_input_from_user_with_timeout(int seconds);