#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include "textAnimator.h"
#include "interactions.h"
#include "question.h"
#include "file.h"

using namespace std;

const float CORRECT_WEIGHT = 1;
const float INCORRECT_WEIGHT = 2;
float TIME_LIMIT = 10;

struct Score
{
    int count, correct, incorrect;
};

void show_gameover(Score round_score)
{
    int total_score = (round_score.correct * CORRECT_WEIGHT) - (round_score.incorrect * INCORRECT_WEIGHT);
    if (round_score.correct >= round_score.count)
    {
        cout << "Game over! You're \033[1;33mAWESOME\033[0m! \nYou answered all the questions correctly!";
        cout << "\n\033[1;33m Total Score : " << total_score << " out of " << round_score.count * CORRECT_WEIGHT << "\033[0m\n\n";
    }
    else if (total_score > (round_score.count * CORRECT_WEIGHT / 4))
    {
        cout << "Game over! Impressive! \nMore than 75 percent of the answers were correct.";
        cout << "\n\033[1;33m Total Score : " << total_score << " out of " << round_score.count * CORRECT_WEIGHT << "\033[0m\n\n";
    }
    else if (total_score > 0)
    {
        cout << "Game over! Could be better! \n";
        cout << "\n\033[1;33m Total Score : " << total_score << " out of " << round_score.count * CORRECT_WEIGHT << "\033[0m\n\n";
    }
    else
    {
        cout << "Game over! You're a \033[1;31mfailure\033[0m! \n";
        cout << "\n\033[1;33m Total Score : Does not worth to mention\033[0m\n\n";
    }
    enter_to_continue();
}

Score start_round(std::list<Question> qlist, int question_count = 20)
{
    print_animated("\n\033[1;33mEach correct answer gives 1 points and each incorrect asnwer costs 2 points!\033[0m\n", 1.5);
    print_animated("\033[1;33mYou will have 10 seconds to answer each question! \n\033[0m\n", 1.5);
    enter_to_continue();
    int correct = 0;
    int incorrect = 0;
    int answered = 0;
    int size = qlist.size();
    for (int i = 0; i < size; i++)
    {
        Question q = qlist.front();
        qlist.pop_front();
        bool r = q.prompt(TIME_LIMIT); // Ask the question to the user
        answered++;
        if (r) // Check if the asnwer is true, if so, increment the correct counter
        {
            correct++;
        }
        else // if not, increment the incorrect counter
        {
            incorrect++;
        }
        if (answered >= question_count) // Check if we reached the last question, if so, break the loop
        {
            break; // Break out of the loop
        }
    }
    while (qlist.size() > 0)
    {
        qlist.pop_front(); // I don't know if cleaning the list is important here but here it is anyway
    }
    clear_screen();
    struct Score round_score = {answered, correct, incorrect};
    show_gameover(round_score);
    return round_score;
}

Score easy_round(int question_count = 20)
{
    std::list<Question> qlist = getquestionsfromfile(".\\data\\questions\\easyQuestions.txt", true);
    return start_round(qlist, question_count);
}
Score normal_round(int question_count = 20)
{
    std::list<Question> qlist = getquestionsfromfile(".\\data\\questions\\normalQuestions.txt", true);
    return start_round(qlist, question_count);
}
Score hard_round(int question_count = 20)
{
    std::list<Question> qlist = getquestionsfromfile(".\\data\\questions\\hardQuestions.txt", true);
    return start_round(qlist, question_count);
}
Score mixed_round(int question_count = 30)
{
    std::list<Question> qlist = getallquestions(true);
    return start_round(qlist, question_count);
}
Score full_round()
{
    std::list<Question> qlist = getallquestions(true);
    return start_round(qlist, (int) qlist.size());
}

int main()
{
    clear_screen(); // Always call this first
    unsigned int extra_entropy; // Uninitialized variable. Who knows what it will be.
    srand(time(NULL) + extra_entropy); // Set randomseed from combination of current time and some random value
    while (true)
    {
        clear_screen();
        print_animated("\033[1;33mWelcome to The Quiz Game!\033[0m\n", 1.0);
        print_animated("\033[1;32mPlease select a gamemode \033[0m\n", 1.0);
        print_animated("\033[1;34m 1) Easy (20 questions) \033[0m\n", 0.25);
        print_animated("\033[1;34m 2) Normal (20 questions) \033[0m\n", 0.25);
        print_animated("\033[1;34m 3) Hard (20 questions) \033[0m\n", 0.25);
        print_animated("\033[1;34m 4) Mix (30 questions) \033[0m\n", 0.25);
        print_animated("\033[1;34m 5) All of them (Every question) \033[0m\n", 0.25);
        print_animated("\033[1;34m 0) Exit \033[0m\n", 0.1);
        string input = get_input_from_user();
        if (input == "0")
        {
            break;
        }
        else if (input == "1")
        {
            easy_round(20);
        }
        else if (input == "2")
        {
            normal_round(20);
        }
        else if (input == "3")
        {
            hard_round(20);
        }
        else if (input == "4")
        {
            mixed_round(30);
        }
        else if (input == "5")
        {
            full_round();
        }
        else
        {
            print_animated("\n\033[1;31m Unknown command. Please try again. \033[0m\n", 0.1);
            enter_to_continue();
        }
    }
    return 0;
}