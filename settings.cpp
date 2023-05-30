#include <iostream>
#include <string>
#include <unordered_map>
#include "settings.h"

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