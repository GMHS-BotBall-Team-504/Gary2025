#!/bin/bash
# This script compiles the botball user program and uploads it to the botball robot.

# Copy files to build directories
cd ..
echo Copying files to build directories
sudo cp -r include/ /out/build/
sudo cp -r src/ out/build/

# Compile the botball user program
echo Compiling botball_user_program
sudo docker run -it --rm --volume ./out/build:/home/kipr:rw sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall src/*.c -lkipr -lm -o botball_user_program -lz -lpthread
echo Compiled botball_user_program
cd out/build

# This is the check for either 10.0.0.250 or 192.168.125.1 or 192.168.124.1
echo Sending botball_user_program to the robot
sshpass -p "botball" scp botball_user_program kipr@192.168.137.78:/home/kipr/
echo Sent botball_user_program to the robot
echo Copying botball_user_program to the bin directory
sudo cp botball_user_program ../bin
echo copied
echo Removing build artifacts
rm -r *
cd ../../scripts
echo "Script completed successfully!"