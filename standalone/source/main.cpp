#include <greeter/greeter.h>
#include <greeter/version.h>

#include <dpp/dpp.h>
#include <thread>
#include <chrono>
#include <atomic>

#include "emoji/EmojiWrapper.hpp"

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

std::atomic<bool> stopTimerThread(false);

auto main(int argc, char** argv) -> int
{
  const std::unordered_map<std::string, greeter::LanguageCode> languages{
      {"en", greeter::LanguageCode::EN},
      {"de", greeter::LanguageCode::DE},
      {"es", greeter::LanguageCode::ES},
      {"fr", greeter::LanguageCode::FR},
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

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (result["version"].as<bool>()) {
    std::cout << "Greeter, version " << GREETER_VERSION << std::endl;
    return 0;
  }

  auto langIt = languages.find(language);
  if (langIt == languages.end()) {
    std::cerr << "unknown language code: " << language << std::endl;
    return 1;
  }

  greeter::Greeter greeter(name);
  std::cout << greeter.greet(langIt->second) << std::endl;
  
  Emoji /*💋*/ emojiWrapper;
  
  // token must be in external file due security reasons
  std::ifstream tokenFile("token.txt");
  std::string BOT_TOKEN;
  if (tokenFile.is_open())
  {
      std::getline(tokenFile, BOT_TOKEN);
      tokenFile.close();
  }
  else
  {
      std::cout << "Unable to open authentication token.txt file for reading!" << std::endl;
      return 1;
  }
  
     srand(time(NULL));
    dpp::cluster bot(BOT_TOKEN);
    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand(
        [&](auto event)
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
                std::cout << "tik-tak" << std::endl;
                int a = rand() % 5;
                std::string randomEmoji;

                switch (a)
                {
                case 0:
                    randomEmoji = emojiWrapper.getRandomEmojiFromGroup("Smileys & Emotion");
                    break;
                case 1:
                    randomEmoji = emojiWrapper.getRandomEmojiFromGroup("Animals & Nature");
                    break;
                case 2:
                    randomEmoji = emojiWrapper.getRandomEmojiFromGroup("Food & Drink");
                    break;
                case 3:
                    randomEmoji = emojiWrapper.getRandomEmojiFromGroup("Activities");
                    break;
                case 4:
                    randomEmoji = emojiWrapper.getRandomEmojiFromGroup("Travel & Places");
                    break;
                default:
                    randomEmoji = emojiWrapper.getRandomEmojiFromGroup("Objects");
                    break;
                }

                std::cout << randomEmoji << std::endl;

                dpp::message msg(event.command.channel_id, randomEmoji);
                event.reply(msg);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            if (event.command.get_command_name() == "emojistop")
            {
                stopTimerThread.store(true);
                event.reply("Random Emoji Stopped!");
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
                    dpp::slashcommand("emoji", "Random Emoji Start!", bot.me.id));
                bot.global_command_create(
                    dpp::slashcommand("emojistop", "Random Emoji Stop!", bot.me.id));
            }
        });

    bot.start(dpp::st_wait);

  return 0;
}
