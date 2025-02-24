
#include <MyDiscordBot/version.h>
#include <MyDiscordBot/MyDiscordBot.hpp>
#include <Logger.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

int main()
{
    std::unique_ptr<MyDiscordBot> lib = std::make_unique<MyDiscordBot>(); // cpp14 +
    
    return 0;
}
