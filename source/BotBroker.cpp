#include "MyDiscordBot/BotBroker.hpp"

#include <dpp/dpp.h>
#include "emoji/EmojiWrapper.hpp"

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <fstream>

std::atomic<bool> stopTimerThread(false);
Emoji /*💋*/ emojiWrapper;

BotBroker::BotBroker()
{
    std::ifstream tokenFile(OAUTH_TOKEN_FILE);
    std::string BOT_TOKEN;
    if (tokenFile.is_open())
    {
        std::getline(tokenFile, BOT_TOKEN);
        tokenFile.close();

    }
    else
    {
        std::cout << "Unable to open authentication file for reading!" << std::endl;
        std::cout << OAUTH_TOKEN_FILE << std::endl;
        return;
    }

    dpp::cluster bot(BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand(
        [&bot](auto event)
        {
            using EventType = decltype(event);

            // Tímto způsobem zjistíte, jakého typu je 'event'
            std::cout << typeid(EventType).name() << std::endl;

            if (event.command.get_command_name() == "ping")
            {
                event.reply("Pong!");
            }
            if (event.command.get_command_name() == "hit")
            {
                event.reply("Pot!");
            }

            if (event.command.get_command_name() == "emoji")
            {
                std::cout << "emoji" << std::endl;
                std::string randomEmoji;
                emojiWrapper.getRandomEmoji(randomEmoji);
                dpp::message msg(event.command.channel_id, randomEmoji);
                event.reply(msg);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            if (event.command.get_command_name() == "stopemojitimer")
            {
                stopTimerThread.store(true);
                event.reply("Random Emoji Timer Stopped!");
            }

            if (event.command.get_command_name() == "startemojitimer")
            {
                std::cout << "startemojitimer" << std::endl;
                std::string randomEmoji;
                emojiWrapper.getRandomEmoji(randomEmoji);
              
                
                // reply required
                dpp::message msg(event.command.channel_id, "OK");
                event.reply(msg);
                
                std::this_thread::sleep_for(std::chrono::seconds(1));

                stopTimerThread.store(false);
                std::thread threadTimer(
                    [&bot, &event]() -> void
                    {
                        while (!stopTimerThread.load())
                        {
                            std::cout << ". Tick ." << std::endl;
                            
                            std::string randomEmoji;
                            emojiWrapper.getRandomEmoji(randomEmoji);

                            dpp::message msg(event.command.channel_id, randomEmoji);
                            bot.message_create(msg);

                            std::cout << randomEmoji << std::endl;
                            std::this_thread::sleep_for(std::chrono::seconds(EMOJI_INTERVAL_SEC));
                        }
                    });

                threadTimer.detach();
            }
        });

    // Register the commands when the bot is ready - is happening every time the
    // bot is network ready
    bot.on_ready(
        [&bot](auto event)
        {
            // Register the commands only once
            if (dpp::run_once<struct register_bot_commands>())
            {
                /* Register the command */
                dpp::slashcommand command("pm", "Send a private message.", bot.me.id);

                /* Add the option fo`r a user mention that isn't required */
                command.add_option(
                    dpp::command_option(dpp::co_mentionable, "user", "The user to message", false));

                /* Register the command */
                bot.global_command_create(command);

                bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
                bot.global_command_create(dpp::slashcommand("hit", "Hit Pot!", bot.me.id));

                bot.global_command_create(
                    dpp::slashcommand("emoji", "Show Random Emoji!", bot.me.id));

                bot.global_command_create(
                    dpp::slashcommand("startemojitimer", "Start Random Emoji Timer!", bot.me.id));

                bot.global_command_create(
                    dpp::slashcommand("stopemojitimer", "Stop Random Emoji Timer!", bot.me.id));
            }
        });

    bot.start(dpp::st_wait);

}

BotBroker::~BotBroker()
{

}