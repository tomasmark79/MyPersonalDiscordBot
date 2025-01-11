#include "MyDiscordBot/MyDiscordBot.hpp"
#include <mydiscordbot/version.h>

#include <EmojiTools/EmojiTools.hpp>
#include <curl/curl.h>
#include <fmt/format.h>

#include <array>
#include <chrono>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <thread>

#ifdef _WIN32
#include <cstdio>
#define popen  _popen
#define pclose _pclose
#else
#include <cstdio>
#endif

#define EMOJI_INTERVAL_SEC (int)10

#define DISCORD_OAUTH_TOKEN_FILE "/home/tomas/.discord_oauth.key"

#define URL_COIN_GECKO "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd"

#define URL_EXCHANGE_RATES_CZ                                                                      \
    "https://www.cnb.cz/cs/financni-trhy/devizovy-trh/kurzy-devizoveho-trhu/"                      \
    "kurzy-devizoveho-trhu/denni_kurz.txt"

std::unique_ptr<dpp::cluster> bot;
// std::unique_ptr<MyGitHubApi>  gitHub;

EmojiTools  emojiTools;
std::string emoji;

const dpp::snowflake channelDev = 1327591560065449995;

std::atomic<bool> stopRefreshMessageThread(false);
#define REGULAR_REFRESH_MESSAGE_INTERVAL_SEC (int)10800 // 3 hours

std::atomic<bool> stopGetBitcoinPrice(false);
#define BITCOIN_PRICE_MESSAGE_INTERVAL_SEC (int)21600 // 6 hours

std::atomic<bool> stopGetGithubInfo(false);
#define GITHUB_INFO_MESSAGE_INTERVAL_SEC (int)43200 // 12 hours

std::atomic<bool> stopGetCzechExchangeRates(false);
#define CZECH_EXCHANGERATES_MESSAGE_INTERVAL_SEC (int)43200 * 2 // 24 hours

std::atomic<bool> stopGithubEventPooling(false);
#define GITHUB_EVENT_POLLING_INTERVAL_SEC (int)10

MyDiscordBot::MyDiscordBot()
{
    std::cout << "--- MyDiscordBot v." << MYDISCORDBOT_VERSION << " instantiated ---" << std::endl;
    std::cout << "--- " << curl_version() << " linked ---" << std::endl;
    // gitHub = std::make_unique<MyGitHubApi>();
    initCluster();
}

MyDiscordBot::~MyDiscordBot()
{
    std::cout << "--- MyDiscordBot uninstantiated ---" << std::endl;
}

bool MyDiscordBot::initCluster()
{
    if (bot)
    {
        std::cerr << "Bot is already initialized!" << std::endl;
        return false;
    }
    std::string token;
    if (getToken(token, DISCORD_OAUTH_TOKEN_FILE))
    {
        bot =
            std::make_unique<dpp::cluster>(token, dpp::i_default_intents | dpp::i_message_content);

        welcomeWithNeofetch();
        startPollingFortune();
        startPollingBTCPrice();
        startPollingCZExchRate();
        loadVariousBotCommands();
        bot->start(dpp::st_wait);
    }
    return true;
}

bool MyDiscordBot::welcomeWithNeofetch()
{
    // DSDotBot loaded
    bot->on_ready(
        [&](const dpp::ready_t &event)
        {
            dpp::message msg(channelDev, "DSDotBot loaded:\n");
            bot->message_create(msg);
            try
            {
                dpp::message msgNeofetch(
                    channelDev, this->getLinuxNeofetchCpp().substr(0, 1998) + "\n"
                );
                bot->message_create(msgNeofetch);
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    );
    return true;
}

bool MyDiscordBot::startPollingFortune()
{
    bot->on_ready(
        [&](const dpp::ready_t &event)
        {
            std::thread threadRegularRefreshMessage(
                [&]() -> void
                {
                    while (!stopRefreshMessageThread.load())
                    {
                        try
                        {
                            std::string message = getLinuxFortuneCpp();
                            // std::cout << message << std::endl;
                            dpp::message msg(channelDev, "Quote\n\t" + message);
                            bot->message_create(msg);
                        }
                        catch (const std::runtime_error &e)
                        {
                            std::cerr << "Error: " << e.what() << std::endl;
                        }

                        std::this_thread::sleep_for(
                            std::chrono::seconds(REGULAR_REFRESH_MESSAGE_INTERVAL_SEC)
                        );
                    }
                }
            );
            threadRegularRefreshMessage.detach();
        }
    );
    return true;
}

bool MyDiscordBot::startPollingBTCPrice()
{
    bot->on_ready(
        [&](const dpp::ready_t &event)
        {
            std::thread threadBitcoinPriceMessage(
                [&]() -> void
                {
                    while (!stopGetBitcoinPrice.load())
                    {
                        try
                        {
                            std::string message = getBitcoinPrice();
                            // std::cout << message << std::endl;
                            dpp::message msg(channelDev, "\n🪙 " + message);
                            bot->message_create(msg);
                        }
                        catch (const std::runtime_error &e)
                        {
                            std::cerr << "Error: " << e.what() << std::endl;
                        }

                        std::this_thread::sleep_for(
                            std::chrono::seconds(BITCOIN_PRICE_MESSAGE_INTERVAL_SEC)
                        );
                    }
                }
            );
            threadBitcoinPriceMessage.detach();
        }
    );
    return true;
}

// TODO Draw as bitmap table will looks better 😎
bool MyDiscordBot::startPollingCZExchRate()
{
    bot->on_ready(
        [&](const dpp::ready_t &event)
        {
            std::thread threadCzechExchangeRateMessage(
                [&]() -> void
                {
                    while (!stopGetCzechExchangeRates.load())
                    {
                        try
                        {
                            std::string message = getCzechExchangeRate();
                            // std::cout << message << std::endl;
                            dpp::message msg(channelDev, "Czech Exchange Rates 🇨🇿\n" + message);
                            bot->message_create(msg);
                        }
                        catch (const std::runtime_error &e)
                        {
                            std::cerr << "Error: " << e.what() << std::endl;
                        }

                        std::this_thread::sleep_for(
                            std::chrono::seconds(CZECH_EXCHANGERATES_MESSAGE_INTERVAL_SEC)
                        );
                    }
                }
            );
            threadCzechExchangeRateMessage.detach();
        }
    );

    return true;
}

bool MyDiscordBot::getToken(std::string &token, const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
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

std::string MyDiscordBot::getLinuxFortuneCpp()
{
    constexpr size_t  bufferSize = 2000;
    std::stringstream result;

    // Create unique_ptr with custom deleter for RAII
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("fortune", "r"), pclose);
    if (!pipe)
        throw std::runtime_error("Failed to run fortune command");

    std::array<char, bufferSize> buffer;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result << buffer.data();
        if (result.str().size() > bufferSize - 2)
            break;
    }

    return result.str();
}

std::string MyDiscordBot::getLinuxNeofetchCpp()
{
    constexpr size_t  bufferSize = 2000;
    std::stringstream result;

    // Create unique_ptr with custom deleter for RAII
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("neofetch --stdout", "r"), pclose);
    if (!pipe)
        throw std::runtime_error("Failed to run neofetch command");

    std::array<char, bufferSize> buffer;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result << buffer.data();
        if (result.str().size() > bufferSize - 2)
            break;
    }

    return result.str();
}

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string MyDiscordBot::getBitcoinPrice()
{
    CURL       *curl;
    CURLcode    res;
    std::string rawTxtBuffer;
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); /* temporary - todo cert */
        curl_easy_setopt(curl, CURLOPT_URL, URL_COIN_GECKO);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rawTxtBuffer);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
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

            std::cout << "Downloaded content:\n" << rawTxtBuffer << std::endl;

            std::string message = "1 BTC = " + usd + " USD";

            std::cout << message << std::endl;

            return message;
        }

        curl_easy_cleanup(curl);
    }
    return "Error: Could not get the Bitcoin price!";
}

std::string MyDiscordBot::getCzechExchangeRate()
{
    CURL       *curl;
    CURLcode    res;
    std::string rawTxtBuffer;
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); /* temporary - todo cert */
        curl_easy_setopt(curl, CURLOPT_URL, URL_EXCHANGE_RATES_CZ);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rawTxtBuffer);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            // replace char "|" with "\t"
            std::replace(rawTxtBuffer.begin(), rawTxtBuffer.end(), '|', '\t');
            // std::cout << "Downloaded content:\n" << rawTxtBuffer << std::endl;
            return rawTxtBuffer;
        }
        curl_easy_cleanup(curl);
    }

    return "Error: Could not get the Czech exchange rate!";
}

bool MyDiscordBot::loadVariousBotCommands()
{
    bot->on_slashcommand(
        [&](const dpp::slashcommand_t &event)
        {
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
        }
    );

    bot->on_ready(
        [&](const dpp::ready_t &event)
        {
            /* ping */
            bot->global_command_create(dpp::slashcommand("ping", "Ping pong!", bot->me.id));

            /* pong */
            bot->global_command_create(dpp::slashcommand("pong", "Pong ping!", bot->me.id));

            /* gang */
            bot->global_command_create(dpp::slashcommand("gang", "Will shoot!", bot->me.id));
        }
    );

    return true;
}

std::string MyDiscordBot::getCurrentTime()
{
    time_t    now = time(0);
    struct tm tstruct;
    char      buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

int MyDiscordBot::getRandom(int min, int max)
{
    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    int                             random = dis(gen);
    return random;
}
