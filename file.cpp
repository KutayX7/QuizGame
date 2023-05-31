#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <list>
#include <unordered_map>
#include "question.h"
#include "file.h"
#include "user.h"

// A cheap fix for question indices
std::list<Question> fix_question_list_order(std::list<Question> qlist)
{
    std::list<Question> qlist_temp;
    int size_l = qlist.size();
    for (int i = 0; i < size_l; i++)
    {
        Question q = qlist.front();
        qlist.pop_front();
        q.id = i;
        q.index = i + 1;
        qlist_temp.push_back(q);
    }
    return qlist_temp;
}

// Combines two list into one
std::list<Question> combine_question_lists(std::list<Question> qlist1, std::list<Question> qlist2)
{
    int size_l1 = qlist1.size();
    int size_l2 = qlist2.size();
    std::list<Question> qlist_temp;
    for (int i = 0; i < size_l1; i++)
    {
        Question q = qlist1.front();
        qlist1.pop_front();
        qlist_temp.push_back(q);
    }
    for (int i = 0; i < size_l2; i++)
    {
        Question q = qlist2.front();
        qlist2.pop_front();
        qlist_temp.push_back(q);
    }
    return fix_question_list_order(qlist_temp);
}

// Rnadomizes the order of elements in the list.
// TODO: Improve the performance.
std::list<Question> randomize_question_list(std::list<Question> qlist)
{
    int size = qlist.size();
    int *indexArr = new int[size];
    for (int i = 0; i < size; i++)
    {
        indexArr[i] = -1;
    }
    for (int i = 0; i < size; i++)
    {
        int rnum = 0;
        bool found = false;
        do
        {
            rnum = std::rand() % size;
            found = false;
            for (int j = 0; j < size; j++)
            {
                if (indexArr[j] == rnum)
                {
                    found = true;
                    break;
                }
            }
        } while (found);
        indexArr[i] = rnum;
    }
    std::list<Question> qlist_temp;
    for (int i = 0; i < size; i++)
    {
        Question q = qlist.front();
        qlist.pop_front();
        q.id = indexArr[i];
        q.index = indexArr[i] + 1;
        qlist_temp.push_back(q);
    }
    delete[] indexArr; // Cleans up memory. DO NOT REMOVE THIS LINE!!!
    qlist_temp.sort();
    return qlist_temp;
}

// Get questions from a file
// When randomOrder is true, questions will be ordered randomly.
std::list<Question> get_questions_from_file(std::string fileName, bool randomOrder)
{
    std::ifstream file;
    file.open(fileName , std::fstream::in);
    std::list<Question> qlist;
    if (!file.is_open())
    {
        std::cout << "\n\033[1;31m Error while reading questions from file\033[0m \"" + fileName + " ! Can not open the file!\"\n";
        return qlist;
    }
    while (!file.eof())
    {
        std::string line = "";
        std::getline(file, line);
        if (line.length() < 1)
        {
            continue;
        }
        if (line.length() >= 2)
        {
            if (line.substr(0, 2) == "//")
            {
                continue;
            }
        }
        Question q = Question();
        q.question = line;
        for (int i = 0; i < 4; i++)
        {
            if (file.eof())
            {
                std::cout << "\n\033[1;31m Error while reading questions from file\033[0m \"" + fileName + "\" ! Reached EOF before reading the options.\n";
                return qlist;
            }
            std::string option = "";
            std::getline(file, option);
            q.options[i] = option;
        }
        if (file.eof())
        {
            std::cout << "\n\033[1;31m Error while reading questions from file\033[0m \"" << fileName << "\" ! Reached EOF before reading the correct option.\n";
            return qlist;
        }
        std::string copt = "";
        std::getline(file, copt);
        if (file.eof() || (copt.length() < 1))
        {
            std::cout << "\n\033[1;31m Error while reading questions from file\033[0m \"" + fileName + "\" ! Reached EOF before reading the description.\n";
            return qlist;
        }
        switch (copt[0])
        {
        case '1':
            q.correct_option = 0;
            break;
        case '2':
            q.correct_option = 1;
            break;
        case '3':
            q.correct_option = 2;
            break;
        case '4':
            q.correct_option = 3;
            break;
        default:
            std::cout << "\n\033[1;31m Error while reading questions from file\033[0m \"" + fileName + "\" ! The correct option is corrupted.\n";
            q.correct_option = 2;
            break;
        }
        std::string desc = "";
        std::getline(file, desc);
        q.description = desc;
        qlist.push_back(q);
    }
    file.close();
    if (randomOrder)
    {
        return randomize_question_list(qlist);
    }
    return fix_question_list_order(qlist);
}
std::list<Question> getquestionsfromfile(std::string fileName, bool randomOrder)
{
    return get_questions_from_file(fileName, randomOrder);
}

// Returns all the questions from all the files
// When randomOrder is true, questions will be ordered randomly.
std::list<Question> get_all_questions(bool randomOrder)
{
    // auto ql1 = get_questions_from_file("./data/questions/generalQuestions.txt", randomOrder); // Not in use for now.
    auto ql2 = get_questions_from_file("./data/questions/easyQuestions.txt", randomOrder);
    auto ql3 = get_questions_from_file("./data/questions/normalQuestions.txt", randomOrder);
    auto ql4 = get_questions_from_file("./data/questions/hardQuestions.txt", randomOrder);
    auto cql = combine_question_lists(combine_question_lists(ql2, ql3), ql4);
    if (randomOrder)
    {
        return randomize_question_list(cql);
    }
    return fix_question_list_order(cql);
}
std::list<Question> getallquestions(bool randomOrder)
{
    return get_all_questions(randomOrder);
}

// Clears the contents of the "userdata.txt" file.
bool erase_all_user_data()
{
    std::ofstream file;
    file.open("./data/userdata.txt", std::ofstream::out | std::ofstream::trunc);
    if (!file.is_open())
    {
        return false;
    }
    file.close();
    return true;
}

std::list<User> load_user_data()
{
    std::list<User> users;
    std::ifstream file;
    file.open("./data/userdata.txt", std::ofstream::in);
    while (!file.eof())
    {
        std::string name = "", score = "";
        std::getline(file, name);
        if (name.length() < 1)
        {
            continue;
        }
        if (file.eof())
        {
            break;
        }
        std::getline(file, score);
        if (score.length() < 1)
        {
            score = "0";
        }
        int score_int = 0;
        try
        {
            score_int = std::stoi(score);
        }
        catch(const std::exception& e)
        {
            score_int = -1;
        }
        User user = User(name, score_int);
        users.push_back(user);
    }
    file.close();
    return users;
}

bool save_user_data(std::list<User> users)
{
    int size = users.size();
    std::ofstream file;
    file.open("./data/userdata.txt", std::ofstream::out | std::ofstream::trunc);
    if (!file.is_open())
    {
        return false;
    }
    for (int i = 0; i < size; i++)
    {
        User user = users.front();
        users.pop_front();
        file << user.serialize();
    }
    file.close();
    return true;
}