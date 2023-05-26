#include <iostream>
#include <string>
#include <unordered_map>
#include "user.h"
#include "interactions.h"

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

LeaderBoard::LeaderBoard()
{
    users = std::list<User>();
}

bool LeaderBoard::add(User &user)
{
    int user_count = users.size();
    bool found = false;
    for (int i = 0; i < user_count; i++)
    {
        User user_temp = users.front();
        users.pop_front();
        if (user.name == user_temp.name)
        {
            found = true;
        }
        users.push_back(user_temp);
    }
    if (!found)
    {
        users.push_back(user);
        users.sort();
    }
    return !found;
}

bool LeaderBoard::remove(User &user)
{
    int user_count = users.size();
    bool found = false;
    for (int i = 0; i < user_count; i++)
    {
        User user_temp = users.front();
        users.pop_front();
        if (user.name == user_temp.name)
        {
            found = true;
        }
        else
        {
            users.push_back(user_temp);
        }
    }
    return found;
}

void LeaderBoard::print()
{
    clear_screen();
    int size = users.size();
    users.sort();
    std::cout << "\033[1;32mLeaderboard:\033[0m\n";
    for (int i = 0; i < size; i++)
    {
        User user = users.back();
        users.pop_back();
        users.push_front(user);
        switch (i)
        {
        case 0:
            std::cout << "\033[1;33m1st : " << user.name << " : " << user.score << "\033[0m\n";
            break;
        case 1:
            std::cout << "\033[38;5;9m2nd : " << user.name << " : " << user.score << "\033[0m\n";
            break;
        case 2:
            std::cout << "\033[38;5;8m3rd : " << user.name << " : " << user.score << "\033[0m\n";
            break;
        default:
            std::cout << i + 1 << "th : " << user.name << " : " << user.score << "\n";
            break;
        }
    }
}

Settings::Settings()
{
    map = std::unordered_map<std::string, bool>();
    set("TIMEOUT_ENABLED", true);
    set("AUTO_SAVE", true);
    set("DEBUG_MODE", false);
    set("SUDO_MODE", false);
}

bool Settings::set(std::string setting, bool value)
{
    map[setting] = value;
    if (map[setting] == value)
    {
        return true;
    }
    return false;
}

bool Settings::get(std::string setting)
{
    if (map[setting] == true)
    {
        return true;
    }
    return false;
}
std::string Settings::get_str(std::string setting)
{
    if (map[setting] == true)
    {
        return "ON";
    }
    return "OFF";
}

bool Settings::toggle(std::string setting)
{
    set(setting, !(get(setting)));
    return get(setting);
}