#ifndef __MYDISCORDBOTLIB_H__
#define __MYDISCORDBOTLIB_H__

#include <dpp/dpp.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#define OAUTH_TOKEN_FILE "/home/tomas/.discord_oauth.key"
#define EMOJI_INTERVAL_SEC (int)600

class MyDiscordBotLib
{
  public:
    MyDiscordBotLib();
    ~MyDiscordBotLib();

  protected:
    std::unique_ptr<dpp::cluster> bot;

  private:
    bool getToken(std::string &token);
    bool initCluster();
    void onReady(std::unique_ptr<dpp::cluster> &bot);
    void slashCommands(std::unique_ptr<dpp::cluster> &bot);
};

#endif // __MYDISCORDBOTLIB_H__