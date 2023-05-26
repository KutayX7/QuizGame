#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "question.h"
#include "user.h"

std::list<Question> getquestionsfromfile(std::string fileName, bool randomOrder = false);
std::list<Question> getallquestions(bool randomOrder = false);

// Delete all user data
bool erase_all_user_data();

// Reads users' data from the userdata file
std::list<User> load_user_data();

// Saves users' data to the userdata file
// Deletes previous data
bool save_user_data(std::list<User> users);