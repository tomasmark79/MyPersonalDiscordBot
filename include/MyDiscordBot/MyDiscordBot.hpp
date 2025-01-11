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
    bool startPollingFortune();
    bool startPollingBTCPrice();
    bool startPollingCZExchRate();

    bool welcomeWithNeofetch();
    bool initCluster();
    bool getToken(std::string &token, const std::string &filePath);

    std::string getLinuxFortuneCpp();
    std::string getLinuxNeofetchCpp();
    std::string getBitcoinPrice();
    std::string getCzechExchangeRate();
    std::string getCurrentTime();
    int         getRandom(int min, int max);

    MyDiscordBot();
    ~MyDiscordBot();

    // TODO - ziskavat zajimave predpovedi, napr. pocasi
};

#endif // __MYDISCORDBOT_H__