#!/usr/bin/env bash

touch ~/.bashrc
echo "export DESTDIR=~/pes" >> ~/.bashrc

git submodule update --init --recursive

sudo apt update
sudo apt install -y --allow-downgrades build-essential=12.9ubuntu3 libcjson-dev=1.7.15-1 libgcrypt20-dev=1.9.4-3ubuntu3 openssl=3.0.2-0ubuntu1 libtinyxml2-dev=9.0.0+dfsg-3

sudo apt install -y libgtest-dev=1.11.0-3 cmake-data=3.22.1-1ubuntu1 cmake=3.22.1-1ubuntu1 lcov=1.15-1

# Build CommunicationManager
cd modules/CommunicationManager
make deps && make -j$(nproc)

# Build ImageManager
cd ../..
cd modules/ImageManager
make deps && make -j$(nproc)

# Build LogManager
# TODO

# Build Authenticator
#TODO