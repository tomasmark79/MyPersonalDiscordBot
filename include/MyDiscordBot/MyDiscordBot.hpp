#ifndef __MYDISCORDBOT_H__
#define __MYDISCORDBOT_H__

#include <dpp/dpp.h>
#include <iostream>
#include <memory>
#include <random>
#include <string>

class MyDiscordBot
{
  public:
    bool loadVariousBotCommands();

    bool startRegularlyRefreshMessage();
    bool startRegularlyBitcoinPriceMessage();
    bool startRegularlyCzechExchangeRateMessage();
    bool startRegularlyGithubInfoMessage();

    bool welcome();
    bool initCluster();
    bool getToken(std::string &token, const std::string &filePath);

    std::string getLinuxFortuneCpp();
    std::string getLinuxNeofetchCpp();
    std::string getBitcoinPrice();
    std::string getCzechExchangeRate();
    std::string getGithubInfo(int totalCommits);

    int getRandom(int min, int max)
    {
        std::random_device              rd;
        std::mt19937                    gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        int                             random = dis(gen);
        return random;
    }

    std::string getCurrentTime()
    {
        time_t    now = time(0);
        struct tm tstruct;
        char      buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        return buf;
    }

    MyDiscordBot();
    ~MyDiscordBot();

    // TODO - ziskavat zajimave predpovedi, napr. pocasi

};

#endif // __MYDISCORDBOT_H__