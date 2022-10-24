#!/usr/bin/env bash

INSTALL_PATH=$HOME/pes
mkdir -p $INSTALL_PATH

git submodule update --init --recursive --remote

sudo apt update

# On Ubuntu, all packages are from jammy repository

sudo apt install -y --allow-downgrades build-essential=12.9ubuntu3 libcjson-dev=1.7.15-1 libgcrypt20-dev=1.9.4-3ubuntu3 openssl=3.0.2-0ubuntu1 libtinyxml2-dev=9.0.0+dfsg-3 

sudo apt install -y libgtest-dev=1.11.0-3 cmake-data=3.22.1-1ubuntu1 cmake=3.22.1-1ubuntu1 lcov=1.15-1

# Install Qt

sudo apt install -y --allow-downgrades libqt5concurrent5=5.15.3+dfsg-2 libqt5core5a=5.15.3+dfsg-2 libqt5dbus5=5.15.3+dfsg-2 libqt5gui5=5.15.3+dfsg-2 libqt5network5=5.15.3+dfsg-2 libqt5printsupport5=5.15.3+dfsg-2 libqt5sql5=5.15.3+dfsg-2 libqt5test5=5.15.3+dfsg-2 libqt5widgets5=5.15.3+dfsg-2 libqt5xml5=5.15.3+dfsg-2 qt5-qmake-bin=5.15.3+dfsg-2 qt5-qmake=5.15.3+dfsg-2 qtbase5-dev-tools=5.15.3+dfsg-2 qtbase5-dev=5.15.3+dfsg-2

# Build LogManager
cd modules/LogManager
make slib -j$(nproc) && make smove DESTDIR=$INSTALL_PATH

# Build Authenticator
cd ../
cd authentication
make slib -j$(nproc) && make smove DESTDIR=$INSTALL_PATH

# Build UI_API
cd ../
cd UI_API
make deps DESTDIR=$INSTALL_PATH

# Build CommunicationManager
cd ../
cd CommunicationManager
make deps DESTDIR=$INSTALL_PATH && make -j$(nproc) DESTDIR=$INSTALL_PATH && make install DESTDIR=$INSTALL_PATH

# Build ImageManager
cd ../
cd ImageManager
make deps DESTDIR=$INSTALL_PATH && make -j$(nproc) DESTDIR=$INSTALL_PATH && make install DESTDIR=$INSTALL_PATH

# Install certificate
mkdir -p $INSTALL_PATH/certificate
cd ../..
cp certificate/* $INSTALL_PATH/certificate
