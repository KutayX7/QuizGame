#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include "textAnimator.h"
#include "interactions.h"
#include "question.h"
#include "file.h"

using namespace std;

int main()
{
    print_animated("\033[1;33mWelcome to The Quiz Game! \n\033[0m\n", 1.0);
    std::list<Question> qlist = getallquestions(true);
    int size = qlist.size();
    for (int i;i < size;i++)
    {
        Question q = qlist.front();
        qlist.pop_front();
        q.printq();
    }
    return 0;
}