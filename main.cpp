#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include "textAnimator.h"
#include "interactions.h"
#include "question.h"
#include "file.h"
#include "user.h"

using namespace std;

const float CORRECT_WEIGHT = 1;
const float INCORRECT_WEIGHT = 2;
float TIME_LIMIT = 10;
bool USER_DEBUG_MODE = false;
bool TIMER_ENBALED = true;

Settings SETTINGS;

list<User> USERS;
LeaderBoard LEADERBOARD;

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

int select_mode()
{
    clear_screen();
    print_animated("\033[1;35mWelcome to The Quiz Game!\033[0m\n", 0.75);
    print_animated("\033[1;34mPlease choose a option.\033[0m\n", 0.25);
    print_animated(
    "1) Play\n"
    "2) Leaderboard\n"
    "3) Settings\n"
    "0) Exit\n", 0.5);
    string input = get_input_from_user();
    if (input == "0")
    {
        return 0;
    }
    else if (input == "1")
    {
        return 1;
    }
    else if (input == "2")
    {
        return 2;
    }
    else if (input == "3")
    {
        return 3;
    }
    else
    {
        return -1;
    }
}

int option_play()
{
    clear_screen();
    print_animated("\033[1;32mPlease select a gamemode \033[0m\n", 0.2);
    print_animated(
    "1) Easy (20 questions)\n"
    "2) Normal (20 questions)\n"
    "3) Hard (20 questions)\n"
    "4) Mix (30 questions)\n"
    "5) All of them (Every question)\n"
    "0) Return to main menu\n", 0.5);
    string input = get_input_from_user();
    if (input == "0")
    {
        return 0;
    }
    else if (input == "1")
    {
        easy_round(20);
        return 0;
    }
    else if (input == "2")
    {
        normal_round(20);
        return 0;
    }
    else if (input == "3")
    {
        hard_round(20);
        return 0;
    }
    else if (input == "4")
    {
        mixed_round(30);
        return 0;
    }
    else if (input == "5")
    {
        full_round();
        return 0;
    }
    else
    {
        print_animated("\n\033[1;31m Unknown command. Returning to the main menu. \033[0m\n", 0.1);
        enter_to_continue();
        return 1;
    }
}

int option_settings()
{
    clear_screen();
    print_animated("\033[1;32mOptions: \033[0m\n", 0.2);
    print_animated("Choose a setting to toggle on/off or activate it.\n", 0.2);
    print_animated("1) TIMEOUT_ENABLED : " + SETTINGS.get_str("TIMEOUT_ENABLED") + "\n", 0.1);
    print_animated("2) DEBUG_MODE : " + SETTINGS.get_str("DEBUG_MODE") + "\n", 0.1);
    print_animated("3) SUDO_MODE : " + SETTINGS.get_str("SUDO_MODE") + "\n", 0.1);
    print_animated("4) AUTO_SAVE : " + SETTINGS.get_str("AUTO_SAVE") + "\n", 0.1);
    print_animated("5) Save data now\n", 0.1);
    print_animated("6) Erase all user data (Requires restart)\n", 0.1);
    print_animated("0) Return to main menu\n", 0.1);
    string input = get_input_from_user();
    if (input == "0")
    {
        return 0;
    }
    else if (input == "1")
    {
        SETTINGS.toggle("TIMEOUT_ENABLED");
        return 3;
    }
    else if (input == "2")
    {
        SETTINGS.toggle("DEBUG_MODE");
        return 3;
    }
    else if (input == "3")
    {
        SETTINGS.toggle("SUDO_MODE");
        return 3;
    }
    else if (input == "4")
    {
        SETTINGS.toggle("AUTO_SAVE");
        return 3;
    }
    else if (input == "5")
    {
        bool success = save_user_data(LEADERBOARD.users);
        if (success)
        {
            print_animated("\033[1;32mData saved successfully.\033[0m\n", 0.5);
            enter_to_continue();
        }
        else
        {
            print_animated("\033[1;31mData save failed!\033[0m\n", 0.5);
            if (SETTINGS.get("SUDO_MODE"))
            {
                enter_to_continue();
                return 3;
            }
            else
            {
                print_animated("Exiting program to prevent further data corruption.", 0.5);
                return -1;
            }
        }
        return 3;
    }
    else if (input == "6")
    {
        if (SETTINGS.get("SUDO_MODE"))
        {
            bool success = erase_all_user_data();
            USERS = list<User>();
            LEADERBOARD.users = USERS;
            if (success)
            {
                print_animated("All the user data has been erased successfully.\n", 1.0);
                return 1;
            }
            else
            {
                print_animated("\033[1;33mAn unexpected \033[1;31merror\033[1;33m has happened during data deletion.\033[0m\n", 1.0);
                print_animated("The program has to exit.\n", 1.0);
                return -1;
            }
        }
        else
        {
            print_animated("\033[1;33mAre you sure you want to delete all the user data?\n", 2.5);
            print_animated("The program will close after this operation.\n", 2.5);
            print_animated("Type \"Yes-I-know-what-I-am-doing-Please-delete-it.\" with the quotation marks.\n If you don't type it correctly this operation will be canceled.\033[0m\n", 1.5);
            std::string input2 = get_input_from_user();
            if (input2 == "\"Yes-I-know-what-I-am-doing-Please-delete-it.\"")
            {
                bool success = erase_all_user_data();
                if (success)
                {
                    print_animated("All the user data has been erased successfully.\n", 1.0);
                    return -1;
                }
                else
                {
                    print_animated("\033[1;33mAn unexpected \033[1;31merror\033[1;33m has happened during data deletion.\033[0m\n", 1.0);
                    print_animated("The program has to exit.\n", 1.0);
                    return -1;
                }
            }
            else
            {
                return 3;
            }
        }
        return -1;
    }
    else
    {
        print_animated("\n\033[1;31m Unknown command. Returning to the main menu. \033[0m\n", 0.1);
        enter_to_continue();
        return 0;
    }
}

int main()
{
    SETTINGS = Settings();
    clear_screen();
    USERS = load_user_data();
    LEADERBOARD = LeaderBoard();
    LEADERBOARD.users = USERS;
    unsigned int extra_entropy; // Uninitialized variable. Who knows what it will be.
    srand(time(NULL) + extra_entropy); // Set randomseed from combination of current time and some random value
    print_animated("\033[1;33mWarning: Do not type anything while the text is being displayed!\033[0m\n", 0.2);
    print_animated("\033[1;33mWarning: Do not scroll or use scroll wheel!\033[0m\n", 0.2);
    print_animated("\033[1;33mWarning: Do not use arrow keys, space key, backspace key or mouse!\033[0m\n", 0.2);
    print_animated("\033[1;33mWarning: Questions can only be answered with digits 1, 2, 3 and 4.\033[0m\n", 0.2);
    print_animated("\033[1;33mWarning: Make sure the window size is enough to display these warnings without any cropping or wrapping.\033[0m\n", 0.2);
    print_animated("\033[1;33mWarning: Do not run 2 or more instances of this program at once!\033[0m\n", 0.2);
    print_animated("\033[1;33mWarning: In the case of the program gets stuck, terminate the program IMMEDIATELY!\033[0m\n", 0.2);
    print_animated("\033[1;33m         Not properly terminating the program will eventually cause your computer to crash!\033[0m\n", 0.2);
    print_animated("\033[1;33m         It happened before! Just saying.\033[0m\n", 0.2);
    print_animated("\033[1;33mWarning: You will not see these warnings again!\033[0m\n\n", 0.2);
    enter_to_continue();
    clear_screen();
    int state = 0;
    while (state > -1)
    {
        if (state == 0)
        {
            state = select_mode();
        }
        switch (state)
        {
        case 0:
            state = -1;
            break;
        case 1:
            state = option_play();
            break;
        case 2:
            LEADERBOARD.print();
            enter_to_continue();
            state = 0;
            break;
        case 3:
            state = option_settings();
            break;
        default:
            print_animated("\n\033[1;31m Unknown command.\033[0m\n", 0.1);
            enter_to_continue();
            state = 0;
            break;
        }
    }
    print_animated("\033[1;33mGoodbye!\033[0m\n", 1.0);
    enter_to_continue();
    return 0;
}