#!/bin/bash

# Move up one directory
cd ..

# Remove previous build directory if it exists
sudo rm -rf out/build

# Create build directory with proper permissions
sudo mkdir -p out/build
sudo chmod 777 out/build

# Fix path syntax and use proper cp commands for copying the necessary directories
sudo cp -r include/ out/build/
sudo cp -r src/ out/build/

# Set permissions for the copied files and directories
sudo chmod -R 777 out/build/

# Run Docker with explicit user permissions (ensure user matches current user)
sudo docker run -it --rm --user $(id -u):$(id -g) \
    --volume "$(pwd)/out/build:/home/kipr:rw" \
    sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall -pthread \
    src/main.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c -lkipr -lm -o botball_user_program

# Return to the original scripts directory
cd scripts