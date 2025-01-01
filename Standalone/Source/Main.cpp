
#include <MyDiscordBot/MyDiscordBot.hpp>
#include <mydiscordbot/version.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

int main()
{
    std::unique_ptr<MyDiscordBot> Lib = std::make_unique<MyDiscordBot>(); // cpp14 +
    // std::unique_ptr<MyDiscordBot> Lib(new MyDiscordBot()); // cpp11 +

    // remove me ------------------👇🏻
    std::cout << "Wait for 5 seconds please ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Bye bye!" << std::endl;
    // remove me ------------------👆🏻

    return 0;
}
