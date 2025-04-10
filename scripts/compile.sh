#!/bin/bash
# This script compiles the botball user program and uploads it to the botball robot.

# Copy files to build directories
echo Copying files to build directories
sudo cp -r include/ /out/build/
sudo cp -r src/ out/build/

# Compile the botball user program
echo Compiling botball_user_program
sudo docker run -it --rm --volume ./out/build:/home/kipr:rw sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall src/*.c -lkipr -lm -o botball_user_program -lz -lpthread
echo Compiled botball_user_program
cd out/build

# Copy and remove build artifacts
echo Copying botball_user_program to the bin directory
sudo cp botball_user_program ../bin
echo copied
echo Removing build artifacts
rm -r *
cd ..
echo "Script completed successfully!"