#!/bin/bash

rm buffer.txt
# make re && ./IRC 8080 lolcat
# make clean
make re && valgrind --leak-check=full ./IRC 8080 lolcat
# /connect localhost 8080 lolcat