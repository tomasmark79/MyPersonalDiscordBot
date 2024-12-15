#include "MyDiscordBotLib/MyDiscordBotLib.hpp"

// #include <curl/curl.h>

#include <EmojiToolsLib/EmojiToolsLib.hpp>
#include <iostream>
#include <memory>

MyDiscordBotLib::MyDiscordBotLib()
{
    EmojiToolsLib /*💋*/ emojiTools;
    std::string emoji;
    
    std::cout << "-- MyDiscordBot Library Linked --" << " " << emojiTools.getRandomEmoji(emoji) << std::endl;
    initCluster();
}

MyDiscordBotLib::~MyDiscordBotLib() { std::cout << "Bye Bye!" << std::endl; }

void MyDiscordBotLib::slashCommands(std::unique_ptr<dpp::cluster> &bot)
{
    bot->on_log(dpp::utility::cout_logger());

    // lambda access to the bot object
    bot->on_slashcommand(
        [&](const dpp::slashcommand_t &event)
        {
            std::cout << typeid(event).name() << std::endl; // is showing type of event

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
        });
}

void MyDiscordBotLib::onReady(std::unique_ptr<dpp::cluster> &bot)
{
    std::cout << "Ready event" << std::endl;

    // Register the commands when the bot is ready - is happening every time the
    // bot is network ready
    bot->on_ready(
        [&](auto event)
        {
            // Register the commands only once
            if (dpp::run_once<struct register_bot_commands>())
            {
                /* pm */
                dpp::slashcommand command("pm", "Send a private message.", bot->me.id);
                command.add_option(
                    dpp::command_option(dpp::co_mentionable, "user", "The user to message", false));
                bot->global_command_create(command);

                /* getbotinfo */
                bot->global_command_create(
                    dpp::slashcommand("bot", "Get bot information!", bot->me.id));

                /* ping */
                bot->global_command_create(dpp::slashcommand("ping", "Ping pong!", bot->me.id));

                /* pong */
                bot->global_command_create(dpp::slashcommand("pong", "Pong ping!", bot->me.id));

                /* gang */
                bot->global_command_create(dpp::slashcommand("gang", "Will shoot!", bot->me.id));

                /* emoji */
                bot->global_command_create(dpp::slashcommand(
                    "emoji", "Show random emoji character to the chat!", bot->me.id));

                bot->global_command_create(dpp::slashcommand(
                    "fewemojies", "Show random number of random emoji characters in interval!",
                    bot->me.id));

                bot->global_command_create(
                    dpp::slashcommand("noemoji", "Stop to all incomming emojies!", bot->me.id));

                bot->global_command_create(
                    dpp::slashcommand("exchange", "Get latest exchange rates!", bot->me.id));

                std::cout << "Commands registered!" << std::endl;
            }
        });
}

bool MyDiscordBotLib::initCluster()
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

bool MyDiscordBotLib::getToken(std::string &token)
{
    std::ifstream file(OAUTH_TOKEN_FILE);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << OAUTH_TOKEN_FILE << std::endl;
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
