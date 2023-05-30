#include <iostream>
#include <string>
#include "user.h"
#include "interactions.h"

User::User()
{
    name = "unnamed";
    score = 0;
};
User::User(std::string _name, int _score)
{
    name = _name;
    score = _score;
}

std::string User::serialize()
{
    std::string scoreStr = std::to_string(score);
    return name + "\n" + scoreStr + "\n";
}

bool User::operator<(User &user2)
{
    return (score < user2.score);
}
bool User::operator>(User &user2)
{
    return (score > user2.score);
}
bool User::operator==(User user2)
{
    return (this->name == user2.name);
}

LeaderBoard::LeaderBoard()
{
    users = std::list<User>();
}

bool LeaderBoard::add(User &user)
{
    int user_count = users.size();
    bool found = false;
    for (std::list<User>::iterator it = users.begin(); it != users.end(); it++)
    {
        if (it->name == user.name)
        {
            found = true;
        }
    }
    if (!found)
    {
        users.push_back(user);
    }
    return !found;
}

bool LeaderBoard::remove(User &user)
{
    int user_count = users.size();
    bool found = false;
    int f_index = 0;
    int i = 0;
    for (std::list<User>::iterator it = users.begin(); it != users.end(); it++)
    {
        if (user.name == it->name)
        {
            found = true;
        }
        i++;
    }
    if (found)
    {
        users.remove(user);
    }
    return found;
}

void LeaderBoard::print()
{
    clear_screen();
    int size = users.size();
    users.sort();
    std::cout << "\033[1;32mLeaderboard:\033[0m\n";
    int i = 0;
    for (std::list<User>::reverse_iterator it = users.rbegin(); it != users.rend(); it++)
    {
        switch (i)
        {
        case 0:
            std::cout << "\033[1;33m1st : " << it->name << " : " << it->score << "\033[0m\n";
            break;
        case 1:
            std::cout << "\033[38;5;9m2nd : " << it->name << " : " << it->score << "\033[0m\n";
            break;
        case 2:
            std::cout << "\033[38;5;8m3rd : " << it->name << " : " << it->score << "\033[0m\n";
            break;
        default:
            std::cout << i + 1 << "th : " << it->name << " : " << it->score << "\n";
            break;
        }
        i++;
    }
}