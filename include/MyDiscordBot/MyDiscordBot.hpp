#ifndef __MYDISCORDBOT_H__
#define __MYDISCORDBOT_H__

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "dpp/dpp.h"

#define OAUTH_TOKEN_FILE   "/home/tomas/.discord_oauth.key"
#define EMOJI_INTERVAL_SEC (int)600

// Library declaration

class MyDiscordBot
{
  public:
    MyDiscordBot();
    ~MyDiscordBot();

  protected:
    std::unique_ptr<dpp::cluster> bot;

  private:
    bool getToken(std::string &token);
    bool initCluster();
    void onReady(std::unique_ptr<dpp::cluster> &bot);
    void slashCommands(std::unique_ptr<dpp::cluster> &bot);
};

#endif // __MYDISCORDBOT_H__