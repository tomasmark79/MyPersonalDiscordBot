#!/bin/bash
# Script for copying build artifacts to remote server

AARCH64_BIN_STAND="/home/tomas/dev/cpp/projects/mydiscordbot/standalone/build-aarch64"
DEST="tomas@devbox-air:/home/tomas/apps/MyDiscordBot/"
SSH_OPTS=(-e "ssh -p 7922")

rsync -avz "${SSH_OPTS[@]}" $AARCH64_BIN_STAND/MyDiscordBotStandalone $DEST
rsync -avz "${SSH_OPTS[@]}" $AARCH64_BIN_STAND/_deps/emojitools-build/libEmojiTools.* $DEST
rsync -avz "${SSH_OPTS[@]}" $AARCH64_BIN_STAND/_deps/dpp-build/library/libdpp.* $DEST
rsync -avz "${SSH_OPTS[@]}" $AARCH64_BIN_STAND/_deps/fmt-build/libfmtd.* $DEST
rsync -avz "${SSH_OPTS[@]}" $AARCH64_BIN_STAND/_deps/mydiscordbotlib-build/libMyDiscordBotLib.* $DEST
