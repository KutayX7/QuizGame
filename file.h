#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "Question.h"

std::list<Question> getquestionsfromfile(std::string fileName, bool randomOrder = false);
std::list<Question> getallquestions(bool randomOrder = false);