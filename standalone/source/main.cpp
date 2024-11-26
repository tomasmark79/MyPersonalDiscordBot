#include "emoji/EmojiWrapper.hpp"

#include <atomic>
#include <chrono>
#include <cxxopts.hpp>
#include <dpp/dpp.h>
#include <greeter/greeter.h>
#include <greeter/version.h>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>

// ten minutes
#define EMOJI_INTERVAL_SEC (int) 600
#define OAUTH_TOKEN_FILE "/home/tomas/.discord_oauth.key"

std::atomic<bool> stopTimerThread(false);

Emoji /*💋*/ emojiWrapper;

auto main(int argc, char **argv) -> int
{
    const std::unordered_map<std::string, greeter::LanguageCode> languages{
        {"en", greeter::LanguageCode::EN}, {"de", greeter::LanguageCode::DE},
        {"es", greeter::LanguageCode::ES}, {"fr", greeter::LanguageCode::FR},
        {"cs", greeter::LanguageCode::CS},

    };

    cxxopts::Options options(*argv, "A program to welcome the world!");

    std::string language;
    std::string name;

    // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("n,name", "Name to greet",cxxopts::value(name)->default_value("World"))
    ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  ;
    // clang-format on

    auto result = options.parse(argc, argv);

    if (result["help"].as<bool>())
    {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (result["version"].as<bool>())
    {
        std::cout << "Greeter, version " << GREETER_VERSION << std::endl;
        return 0;
    }

    auto langIt = languages.find(language);
    if (langIt == languages.end())
    {
        std::cerr << "unknown language code: " << language << std::endl;
        return 1;
    }

    greeter::Greeter greeter(name);
    std::cout << greeter.greet(langIt->second) << std::endl;

    srand(time(NULL));

    // token must be in external file due security reasons
    // explicit path is better than relative path due cmake builds locations
    // and bash don't see correct path if it's not explicit
    // todo find more clever way to do this
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
        return 1;
    }

    dpp::cluster bot(BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());

    // https://dpp.dev/10.0.35/

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

    return 0;
}
