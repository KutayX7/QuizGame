#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

class Settings
{
    public:
        std::unordered_map<std::string, bool> map;
        Settings();
        ~Settings() = default;
        bool set(std::string setting, bool value = true);
        bool get(std::string setting);
        std::string get_str(std::string setting);
        bool toggle(std::string setting);
};