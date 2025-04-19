#!/bin/bash

clear

# Define directories and variables
BASE_DIR="$( cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd )"
BUILD_DIR="$BASE_DIR/out/build"
KIPR_ROBOT_IP="10.0.0.250"
KIPR_ROBOT_USER="kipr"
KIPR_ROBOT_PASS="botball"
DEPLOY_DIR="/home/kipr/comp"
SRC_DIR="$BASE_DIR/src" 

# Array of executables to build
EXECUTABLES=("manual" "auto" "main" "start")
SRC_FILES=(
    "src/manual.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c"
    "src/auto.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c"
    "src/main.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c"
    "src/start.c"
)

cd "$BASE_DIR/.."
sudo rm -rf "$BUILD_DIR"
sleep 0.1 

# Create build directory with proper permissions
sudo mkdir -p "$BUILD_DIR"
sudo chmod 777 "$BUILD_DIR"
sleep 0.1 

# Copy include and src
sudo cp -r include/ "$BUILD_DIR/"
sudo cp -r src/ "$BUILD_DIR/"
sudo chmod -R 777 "$BUILD_DIR" 
sleep 0.1 

echo ""

# Build executables using a loop
for ((i=0; i<${#EXECUTABLES[@]}; i++)); do
    EXECUTABLE="${EXECUTABLES[$i]}"
    SOURCE_FILES="${SRC_FILES[$i]}"
    echo "Executing docker command:"
    echo "sudo docker run -it --rm --user \"$(id -u):$(id -g)\" --volume \"$(pwd)/scripts/out/build:/home/kipr:rw\" sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall -pthread $SOURCE_FILES -lkipr -lm -o $EXECUTABLE"
    echo "Attempting to build $EXECUTABLE with sources: $SOURCE_FILES"
    sudo docker run -it --rm --user "$(id -u):$(id -g)" \
        --volume "$(pwd)/scripts/out/build:/home/kipr:rw" \
        sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall -pthread  \
        $SOURCE_FILES -lkipr -lm -o $EXECUTABLE
    echo ""

done
current_directory=$(pwd)
echo "The current directory is: $current_directory"

sleep 0.1

sudo rm -r $(pwd)/scripts/out/build/include $(pwd)/scripts/out/build/src 

echo "" 