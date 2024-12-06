#!/bin/bash

# better rsync
SRC_BASE="/home/tomas/dev/cpp/projects/mydiscordbot/build-aarch64"
STANDALONE_SRC="/home/tomas/dev/cpp/projects/mydiscordbot/standalone/build-aarch64"
DEST="tomas@devbox-air:/home/tomas/apps"
SSH_OPTS=(-e "ssh -p 7922")

rsync -avz "${SSH_OPTS[@]}" $STANDALONE_SRC/MyDiscordBotStandalone $DEST
rsync -avz "${SSH_OPTS[@]}" $SRC_BASE/_deps/dpp-build/library/libdpp.* $DEST
rsync -avz "${SSH_OPTS[@]}" $SRC_BASE/_deps/emojitools-build/libEmojiTools.so $DEST
rsync -avz "${SSH_OPTS[@]}" $SRC_BASE/_deps/fmt-build/libfmt.* $DEST
rsync -avz "${SSH_OPTS[@]}" $SRC_BASE/libMyDiscordBot.so $DEST

# slow scp example
#scp -P 7922 /home/tomas/dev/cpp/projects/mydiscordbot/standalone/build-aarch64/MyDiscordBotStandalone tomas@devbox-air:/home/tomas/apps
#scp -P 7922 /home/tomas/dev/cpp/projects/mydiscordbot/build-aarch64/_deps/dpp-build/library/libdpp.* tomas@devbox-air:/home/tomas/apps
#scp -P 7922 /home/tomas/dev/cpp/projects/mydiscordbot/build-aarch64/_deps/emojitools-build/libEmojiTools.so tomas@devbox-air:/home/tomas/apps
#scp -P 7922 /home/tomas/dev/cpp/projects/mydiscordbot/build-aarch64/_deps/fmt-build/libfmt.* tomas@devbox-air:/home/tomas/apps
#scp -P 7922 /home/tomas/dev/cpp/projects/mydiscordbot/build-aarch64/libMyDiscordBot.so tomas@devbox-air:/home/tomas/apps

