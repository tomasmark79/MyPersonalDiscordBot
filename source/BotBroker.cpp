#include "MyDiscordBot/BotBroker.hpp"

#include "emoji/EmojiWrapper.hpp"

#include <atomic>
#include <chrono>
#include <curl/curl.h>
#include <dpp/dpp.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <unordered_map>

std::atomic<bool> stopTimerThread(false);
Emoji /*💋*/ emojiWrapper;

// Funkce pro zápis dat z libcurl do std::string
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

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

            if (event.command.get_command_name() == "emoji")
            {
                std::cout << "emoji" << std::endl;
                std::string randomEmoji;
                emojiWrapper.getRandomEmoji(randomEmoji);
                dpp::message msg(event.command.channel_id, randomEmoji);
                event.reply(msg);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            if (event.command.get_command_name() == "devizovekurzy")
            {

                CURL *curl;
                CURLcode res;
                std::string readBuffer;
                // sudo apt install libcurl4
                curl = curl_easy_init();
                if (curl)
                {
                    curl_easy_setopt(curl, CURLOPT_URL,
                                     "https://www.cnb.cz/cs/financni-trhy/devizovy-trh/"
                                     "kurzy-devizoveho-trhu/kurzy-devizoveho-trhu/denni_kurz.txt");
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

                    res = curl_easy_perform(curl);
                    if (res != CURLE_OK)
                    {
                        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res)
                                  << std::endl;
                    }
                    else
                    {
                        std::cout << "Downloaded content:\n" << readBuffer << std::endl;
                    }
                    curl_easy_cleanup(curl);
                }

                event.reply("Ziskat devizove kurzy!");
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

                bot.global_command_create(
                    dpp::slashcommand("emoji", "Show Random Emoji!", bot.me.id));

                bot.global_command_create(
                    dpp::slashcommand("startemojitimer", "Start Random Emoji Timer!", bot.me.id));

                bot.global_command_create(
                    dpp::slashcommand("stopemojitimer", "Stop Random Emoji Timer!", bot.me.id));

                bot.global_command_create(
                    dpp::slashcommand("devizovekurzy", "Ziskat devizove kurzy!", bot.me.id));
            }
        });

    bot.start(dpp::st_wait);
}

BotBroker::~BotBroker() {}