#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <list>
#include <unordered_map>
#include "Question.h"
#include "file.h"

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
        for (int i = 0;i < 4;i++)
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
        std::unordered_map<int,bool> m;
        std::list<Question> qlist2;
        int size = qlist.size();
        for (int i = 0;i < size;i++)
        {
            int rnum = 0;
            do
            {
                rnum = std::rand() % size;
            } while (m[rnum]);
            m[rnum] = true;
            Question q = qlist.back();
            qlist.pop_back();
            q.id = rnum;
            q.index = rnum + 1;
            qlist2.push_back(q);
        }
        qlist2.sort();
        return qlist2;
    }
    return qlist;
}

std::list<Question> getallquestions(bool randomOrder)
{
    auto ql1 = getquestionsfromfile(".\\data\\questions\\generalQuestions.txt", randomOrder);
    auto ql2 = getquestionsfromfile(".\\data\\questions\\easyQuestions.txt", randomOrder);
    auto ql3 = getquestionsfromfile(".\\data\\questions\\normalQuestions.txt", randomOrder);
    auto ql4 = getquestionsfromfile(".\\data\\questions\\hardQuestions.txt", randomOrder);
    ql1.merge(ql2);
    ql1.merge(ql3);
    ql1.merge(ql4);
    return ql1;
}