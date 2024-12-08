#include "MyDiscordBot/BotBroker.hpp"

#include <mydiscordbot/version.h>
//#include <unistr.h>
//#include <unistdio.h>

auto main(int argc, char **argv) -> int
{
    // ucs4_t uc;

    // for (uc = 0; uc < 0x80; uc++)
    // {
    //     uint8_t buf[5] = {MAGIC, MAGIC, MAGIC, MAGIC, MAGIC};
    //     int ret;

    //     ret = u8_uctomb(buf, uc, 0);
    //     ASSERT(ret == -2);
    //     ASSERT(buf[0] == MAGIC);

    //     ret = u8_uctomb(buf, uc, 1);
    //     ASSERT(ret == 1);
    //     ASSERT(buf[0] == uc);
    //     ASSERT(buf[1] == MAGIC);
    // }

    BotBroker botBroker;

    return 0;
}
