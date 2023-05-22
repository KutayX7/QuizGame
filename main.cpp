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
    clear_screen(); // Always call this first
    srand(time(NULL));
    print_animated("\033[1;33mWelcome to The Quiz Game! \n\033[0m\n", 1.0);
    std::list<Question> qlist = getallquestions(true);
    enter_to_continue();
    int score = 0;
    int mistakes = 0;
    int size = qlist.size();
    for (int i;i < size;i++)
    {
        Question q = qlist.front();
        qlist.pop_front();
        bool r = q.prompt();
        if (!r)
        {
            mistakes += 1;
            break;
        }
        score++;
    }
    clear_screen();
    if (mistakes > 0)
    {
        cout << "Game over! You're a failure! \n";
        cout << "\n\033[1;33m Total Score : " << score << "\033[0m\n\n";
    }
    else
    {
        cout << "Game over! You're a winner! \n";
        cout << "\n\033[1;33m Total Score : " << score << "\033[0m\n\n";
    }
    
    enter_to_continue();
    return 0;
}