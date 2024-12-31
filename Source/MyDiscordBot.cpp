#include "MyDiscordBot/MyDiscordBot.hpp"

// #include <EmojiTools/EmojiTools.hpp> // yet dissabled
#include <iostream>
#include <mydiscordbot/version.h>

MyDiscordBot::MyDiscordBot()
{
    std::cout << "--- MyDiscordBot v." << MYDISCORDBOT_VERSION << " instantiated ---" << std::endl;
}

MyDiscordBot::~MyDiscordBot()
{
    std::cout << "--- MyDiscordBot uninstantiated ---" << std::endl;
}
