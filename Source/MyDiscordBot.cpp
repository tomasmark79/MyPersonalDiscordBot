#include "MyDiscordBot/MyDiscordBot.hpp"

#include <EmojiToolsLib/EmojiToolsLib.hpp>
#include <iostream>
#include <mydiscordbot/version.h>

#include "bzlib.h"
#include <curl/curl.h>

// Library implementation

MyDiscordBot::MyDiscordBot()
{
    std::cout << "--- MyDiscordBot v." << MYDISCORDBOT_VERSION
              << " instantiated ---" << std::endl;

    EmojiToolsLib /*💋*/ emojiTools;
    std::string          emoji;

    std::cout << "-- MyDiscordBot Library Linked --" << " "
              << emojiTools.getRandomEmoji(emoji) << std::endl;


    std::cout << "--- " << curl_version() << " linked ---" << std::endl;
    std::cout << "--- " << BZ2_bzlibVersion() << " linked ---" << std::endl;

    initCluster();

}

MyDiscordBot::~MyDiscordBot()
{
    std::cout << "--- MyDiscordBot uninstantiated ---" << std::endl;
}

// libcurl to std::string
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

void MyDiscordBot::slashCommands(std::unique_ptr<dpp::cluster> &bot)
{
    bot->on_log(dpp::utility::cout_logger());

    // lambda access to the bot object
    bot->on_slashcommand(
        [&](const dpp::slashcommand_t &event)
        {
            std::cout << typeid(event).name()
                      << std::endl; // is showing type of event

            if (event.command.get_command_name() == "ping")
            {
                event.reply("Pong! 🏓");
            }

            if (event.command.get_command_name() == "pong")
            {
                event.reply("Ping! 🏓");
            }
            
            if (event.command.get_command_name() == "gang")
            {
                dpp::message msg(event.command.channel_id, "Bang bang! 💥💥");
                event.reply(msg);
                bot->message_create(msg);
            }

            if (event.command.get_command_name() == "exchange")
            {
                event.reply("Getting latest exchange rates!");

                CURL       *curl;
                CURLcode    res;
                std::string rawTxtBuffer;
                curl = curl_easy_init();
                if (curl)
                {
                    curl_easy_setopt(curl, CURLOPT_URL, URL_EXCHANGE_RATES_CZ);

                    curl_easy_setopt(
                        curl, CURLOPT_WRITEFUNCTION, WriteCallback
                    );
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rawTxtBuffer);

                    res = curl_easy_perform(curl);

                    if (res != CURLE_OK)
                    {
                        std::cerr << "curl_easy_perform() failed: "
                                  << curl_easy_strerror(res) << std::endl;
                    }
                    else
                    {

                        // replace char "|" with "\t"
                        std::replace(
                            rawTxtBuffer.begin(), rawTxtBuffer.end(), '|', '\t'
                        );

                        std::cout << "Downloaded content:\n"
                                  << rawTxtBuffer << std::endl;

                        dpp::message msg(
                            event.command.channel_id, rawTxtBuffer
                        );
                        bot->message_create(msg);
                    }
                    curl_easy_cleanup(curl);
                }
            }

            // TODO on Raspberry Pi 5 i am getting 
            // curl_easy_perform() failed: SSL peer certificate or SSH remote key was not OK
            
            if (event.command.get_command_name() == "crypto")
            {
                event.reply("Getting latest crypto exchange rates!");

                CURL       *curl;
                CURLcode    res;
                std::string rawTxtBuffer;
                curl = curl_easy_init();
                if (curl)
                {
                    curl_easy_setopt(curl, CURLOPT_URL, URL_COIN_GECKO);

                    curl_easy_setopt(
                        curl, CURLOPT_WRITEFUNCTION, WriteCallback
                    );
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rawTxtBuffer);

                    res = curl_easy_perform(curl);

                    if (res != CURLE_OK)
                    {
                        std::cerr << "curl_easy_perform() failed: "
                                  << curl_easy_strerror(res) << std::endl;
                    }
                    else
                    {

                        // use lohmann json to parse the response
                        /*
                        {
                            "bitcoin": {
                                "usd": 95802
                            }
                        }
                        */

                        nlohmann::json j = nlohmann::json::parse(rawTxtBuffer);
                        std::string    usd = j["bitcoin"]["usd"].dump();

                        std::cout << "Downloaded content:\n"
                                  << rawTxtBuffer << std::endl;

                        std::string message = "1 BTC = " + usd + " USD";

                        std::cout << message << std::endl;

                        dpp::message msg(event.command.channel_id, message);
                        bot->message_create(msg);
                    }

                    curl_easy_cleanup(curl);
                }
            }
        }
    );
}

void MyDiscordBot::onReady(std::unique_ptr<dpp::cluster> &bot)
{
    std::cout << "Ready event" << std::endl;

    // Register the commands when the bot is ready - is happening every time
    // the bot is network ready
    bot->on_ready(
        [&](auto event)
        {
            // Register the commands only once
            if (dpp::run_once<struct register_bot_commands>())
            {
                /* pm */
                dpp::slashcommand command(
                    "pm", "Send a private message.", bot->me.id
                );

                /* add options */
                command.add_option(dpp::command_option(
                    dpp::co_mentionable, "user", "The user to message", false
                ));
                bot->global_command_create(command);

                /* getbotinfo */
                bot->global_command_create(
                    dpp::slashcommand("bot", "Get bot information!", bot->me.id)
                );

                /* ping */
                bot->global_command_create(
                    dpp::slashcommand("ping", "Ping pong!", bot->me.id)
                );

                /* pong */
                bot->global_command_create(
                    dpp::slashcommand("pong", "Pong ping!", bot->me.id)
                );

                /* gang */
                bot->global_command_create(
                    dpp::slashcommand("gang", "Will shoot!", bot->me.id)
                );

                /* exchange */
                bot->global_command_create(dpp::slashcommand(
                    "exchange", "Get latest exchange rates!", bot->me.id
                ));

                /* crypto */
                bot->global_command_create(dpp::slashcommand(
                    "crypto", "Get latest crypto exchange rates!", bot->me.id
                ));

                /* emoji */
                bot->global_command_create(dpp::slashcommand(
                    "emoji",
                    "Show random emoji character to the chat!",
                    bot->me.id
                ));

                /* fewemojies */
                bot->global_command_create(dpp::slashcommand(
                    "fewemojies",
                    "Show random number of random emoji characters in "
                    "interval!",
                    bot->me.id
                ));

                /* noemoji */
                bot->global_command_create(dpp::slashcommand(
                    "noemoji", "Stop to all incomming emojies!", bot->me.id
                ));

                std::cout << "Commands registered!" << std::endl;
            }
        }
    );
}

bool MyDiscordBot::initCluster()
{
    if (bot)
    {
        std::cerr << "Bot is already initialized!" << std::endl;
        return false;
    }

    std::string token;
    if (getToken(token))
    {
        /* smart pointer */
        bot = std::make_unique<dpp::cluster>(token);

        this->onReady(bot);
        this->slashCommands(bot);

        bot->start(dpp::st_wait);
    }

    return true;
}

bool MyDiscordBot::getToken(std::string &token)
{
    std::ifstream file(OAUTH_TOKEN_FILE);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << OAUTH_TOKEN_FILE
                  << std::endl;
        return false;
    }

    std::getline(file, token);

    file.close();
    if (token.empty())
    {
        std::cerr << "Error: Token is empty" << std::endl;
        return false;
    }

    return true;
}
