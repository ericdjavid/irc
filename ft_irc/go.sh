#!/bin/bash

# /connect localhost 8080 lolcat

if [ $# -eq 0 ]; then
    echo "No arguments provided, using normal mode"
    make re && ./ircserv 8080 lolcat
    exit 1
elif [ "$1" == "DEBUG" ]; then
    echo "Using debug mode"
    make re && valgrind --leak-check=full ./ircserv 8080 lolcat DEBUG
    exit 1
else
    echo "Bad argument, try again please"
    exit 1
fi
