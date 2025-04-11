#!/bin/bash
cd ..
# Remove previous build directory
rm -rf out/build
# Create build directory with proper permissions
mkdir -p out/build
chmod 777 out/build

# Fix path syntax and use proper cp commands
cp -r include/ out/build/
cp -r src/ out/build/

# Set permissions for copied files
chmod -R 777 out/build/

# Run Docker with explicit permissions
docker run -it --rm --user $(id -u):$(id -g) --volume "$(pwd)/out/build:/home/kipr:rw" sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall -pthread src/main.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c -lkipr -lm -o botball_user_program

cd scripts