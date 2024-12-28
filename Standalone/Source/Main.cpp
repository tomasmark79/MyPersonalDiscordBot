#include <MyDiscordBot/MyDiscordBot.hpp>
#include <mydiscordbot/version.h>

#include <chrono>
#include <iostream>
// #include <memory>
#include <thread>

// Standalone main entry point

int main()
{
    // init MyDiscordBot instance
    std::unique_ptr<MyDiscordBot> Lib = std::make_unique<MyDiscordBot>();

    // five seconds delay
    std::cout << "Wait for 5 seconds please ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // bye bye
    std::cout << "Bye bye!" << std::endl;

    return 0;
}
