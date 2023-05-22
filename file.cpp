#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <list>
#include <unordered_map>
#include "Question.h"
#include "file.h"

std::list<Question> fix_question_list_order(std::list<Question> qlist)
{
    std::list<Question> qlist2;
    int size_l = qlist.size();
    for (int i = 0; i < size_l; i++)
    {
        Question q = qlist.front();
        qlist.pop_front();
        q.id = i;
        q.index = i + 1;
        qlist2.push_back(q);
    }
    return qlist2;
}

std::list<Question> combine_question_lists(std::list<Question> qlist1, std::list<Question> qlist2) // Not safe!
{
    int size_l1 = qlist1.size();
    int size_l2 = qlist2.size();
    std::list<Question> qlist3;
    for (int i = 0; i < size_l1; i++)
    {
        Question q = qlist1.front();
        qlist1.pop_front();
        qlist3.push_back(q);
    }
    for (int i = 0; i < size_l2; i++)
    {
        Question q = qlist2.front();
        qlist2.pop_front();
        qlist3.push_back(q);
    }
    return fix_question_list_order(qlist3);
}

std::list<Question> randomize_question_list(std::list<Question> qlist) // This has terrible performance! Don't use it on very large lists!
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
    std::list<Question> qlist2;
    for (int i = 0; i < size; i++)
    {
        Question q = qlist.front();
        qlist.pop_front();
        q.id = indexArr[i];
        q.index = indexArr[i] + 1;
        qlist2.push_back(q);
    }
    delete[] indexArr;
    qlist2.sort();
    return fix_question_list_order(qlist2);
}

std::list<Question> getquestionsfromfile(std::string fileName, bool randomOrder)
{
    std::ifstream file (fileName, std::ifstream::in);
    std::list<Question> qlist;
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
                std::cout << "\n\033[1;31m Error while reading questions from file\033[0m \"" + fileName + "\"\n";
                return qlist;
            }
            std::getline(file, q.options[i]);
        }
        if (file.eof())
        {
            std::cout << "\n\033[1;31m Error while reading questions from file\033[0m \"" + fileName + "\"\n";
            return qlist;
        }
        std::string copt;
        std::getline(file, copt);
        if (file.eof() || (copt.length() < 1))
        {
            std::cout << "\n\033[1;31m Error while reading questions from file\033[0m \"" + fileName + "\"\n";
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
            q.correct_option = 2;
            break;
        }
        std::getline(file, q.description);
        qlist.push_back(q);
    }
    if (randomOrder)
    {
        return randomize_question_list(qlist);
    }
    return fix_question_list_order(qlist);
}

std::list<Question> getallquestions(bool randomOrder)
{
    // auto ql1 = getquestionsfromfile(".\\data\\questions\\generalQuestions.txt", randomOrder);
    auto ql2 = getquestionsfromfile(".\\data\\questions\\easyQuestions.txt", randomOrder);
    auto ql3 = getquestionsfromfile(".\\data\\questions\\normalQuestions.txt", randomOrder);
    auto ql4 = getquestionsfromfile(".\\data\\questions\\hardQuestions.txt", randomOrder);
    auto cql = combine_question_lists(ql2, ql3);
    cql = combine_question_lists(cql, ql4);
    return fix_question_list_order(cql);
}