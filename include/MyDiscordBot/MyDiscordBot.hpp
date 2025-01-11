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

    bool welcome();
    bool initCluster();
    bool getToken(std::string &token, const std::string &filePath);

    std::string getLinuxFortuneCpp();
    std::string getLinuxNeofetchCpp();
    std::string getBitcoinPrice();
    std::string getCzechExchangeRate();

    int getRandom(int min, int max);

    std::string getCurrentTime();

    MyDiscordBot();
    ~MyDiscordBot();

    // TODO - ziskavat zajimave predpovedi, napr. pocasi
};

#endif // __MYDISCORDBOT_H__