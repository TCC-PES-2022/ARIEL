#!/usr/bin/env bash

INSTALL_PATH=$HOME/pes

git submodule init
git submodule update --recursive --remote

sudo apt update
sudo apt install -y --allow-downgrades build-essential=12.9ubuntu3 libcjson-dev=1.7.15-1 libgcrypt20-dev=1.9.4-3ubuntu3 openssl=3.0.2-0ubuntu1 libtinyxml2-dev=9.0.0+dfsg-3

sudo apt install -y libgtest-dev=1.11.0-3 cmake-data=3.22.1-1ubuntu1 cmake=3.22.1-1ubuntu1 lcov=1.15-1

# Build CommunicationManager
cd modules/CommunicationManager
make deps DESTDIR=$INSTALL_PATH && make -j$(nproc) DESTDIR=$INSTALL_PATH && make install DESTDIR=$INSTALL_PATH

# Build ImageManager
cd ../
cd ImageManager
make deps DESTDIR=$INSTALL_PATH && make -j$(nproc) DESTDIR=$INSTALL_PATH && make install DESTDIR=$INSTALL_PATH

# Build LogManager
cd ../
cd LogManager
make slib -j$(nproc) && make smove DESTDIR=$INSTALL_PATH

# Build Authenticator
cd ../
cd authentication
make slib -j$(nproc) && make smove DESTDIR=$INSTALL_PATH

# Return to root directory
cd ../..
