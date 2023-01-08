#!/bin/bash

clang-format -n *.c *.h *.cc *cpp

while true; do
    read -r -p "Fix it? (Y/n): " answer
    case $answer in
        [Yy]* ) clang-format -i *.c *.h *.cpp *cc; echo "All done"; break;;
        [Nn]* ) exit;;
        * ) echo "Please answer Y or N.";;
    esac
done
