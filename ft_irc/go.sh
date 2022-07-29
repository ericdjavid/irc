#!/bin/bash

rm buffer.txt
make re && ./IRC 8080 lolcat
# make clean
