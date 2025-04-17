#!/bin/bash

clear

# Initialize progress bar function
progress_bar() {
    local progress=$1
    local total=$2
    local width=50
    local percent=$((progress * 100 / total))
    local filled=$((width * progress / total))
    local empty=$((width - filled))
    bar=""
    for ((i=0; i<filled; i++)); do
        bar+="="
    done
    for ((i=0; i<empty; i++)); do
        bar+=" "
    done
    printf "\r[%s] %3d%%" "$bar" "$percent"
    # No fflush here
}

# Define directories and variables
BASE_DIR="$( cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd )"
BUILD_DIR="$BASE_DIR/out/build"
KIPR_ROBOT_IP="10.0.0.250"
KIPR_ROBOT_USER="kipr"
KIPR_ROBOT_PASS="botball"
DEPLOY_DIR="/home/kipr/trison"
SRC_DIR="$BASE_DIR/src" 

# Array of executables to build
EXECUTABLES=("manual" "auto" "main" "start")
SRC_FILES=(
    "src/manual.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c"
    "src/auto.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c"
    "src/main.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c"
    "src/start.c"
)
TOTAL_STEPS=$(( ${#EXECUTABLES[@]} + 3 ))
CURRENT_STEP=0

# Initial progress display
progress_bar $CURRENT_STEP $TOTAL_STEPS

# Move up one directory 
cd "$BASE_DIR/.."
CURRENT_STEP=$((CURRENT_STEP + 1))
progress_bar $CURRENT_STEP $TOTAL_STEPS
sleep 0.1

sudo rm -rf "$BUILD_DIR"
CURRENT_STEP=$((CURRENT_STEP + 1))
progress_bar $CURRENT_STEP $TOTAL_STEPS
sleep 0.1 

# Create build directory with proper permissions
sudo mkdir -p "$BUILD_DIR"
sudo chmod 777 "$BUILD_DIR"
CURRENT_STEP=$((CURRENT_STEP + 1))
progress_bar $CURRENT_STEP $TOTAL_STEPS
sleep 0.1 

# Copy include and src
sudo cp -r include/ "$BUILD_DIR/"
sudo cp -r src/ "$BUILD_DIR/"
sudo chmod -R 777 "$BUILD_DIR" 
sleep 0.1 


# Build executables using a loop
for ((i=0; i<${#EXECUTABLES[@]}; i++)); do
    EXECUTABLE="${EXECUTABLES[$i]}"
    SOURCE_FILES="${SRC_FILES[$i]}"
    sudo docker run -it --rm --user "$(id -u):$(id -g)" \
        --volume "$(pwd)/out/build:/home/kipr:rw" \
        sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall -pthread \
        $SOURCE_FILES -lkipr -lm -o "/home/kipr/$EXECUTABLE" > /dev/null 2>&1 # Suppress output
    CURRENT_STEP=$((CURRENT_STEP + 1))
    progress_bar $CURRENT_STEP $TOTAL_STEPS
    sleep 0.1
done

echo "" 
