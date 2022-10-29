#!/usr/bin/env bash

cd modules/authentication
make

./login -l "$1" -s "$2" -w
cp shadow ../../
