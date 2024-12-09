#!/bin/bash
# Script for copying build artifacts to remote server

AARCH64_BIN_STAND="/home/tomas/dev/cpp/projects/mydiscordbot/standalone/build-aarch64"
DEST="tomas@devbox-air:/home/tomas/apps/MyDiscordBot/"
SSH_OPTS=(-e "ssh -p 7922")

rsync -avz -e "ssh -p 7922" ./build/aarch64/MyDiscordBotStandalone "tomas@devbox-air:/home/tomas/apps/MyDiscordBot/"
rsync -avz -e "ssh -p 7922" ./build/aarch64/_deps/emojitools-build/libEmojiTools.* "tomas@devbox-air:/home/tomas/apps/MyDiscordBot/"
rsync -avz -e "ssh -p 7922" ./build/aarch64/_deps/dpp-build/library/libdpp.* "tomas@devbox-air:/home/tomas/apps/MyDiscordBot/"
rsync -avz -e "ssh -p 7922" ./build/aarch64/_deps/fmt-build/libfmtd.* "tomas@devbox-air:/home/tomas/apps/MyDiscordBot/"
rsync -avz -e "ssh -p 7922" ./build/aarch64/_deps/mydiscordbotlib-build/libMyDiscordBotLib.* "tomas@devbox-air:/home/tomas/apps/MyDiscordBot/"
