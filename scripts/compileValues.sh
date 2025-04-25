#!/bin/bash

clear

# Define directories and variables
BASE_DIR="$( cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd )"
BUILD_DIR="$BASE_DIR/out/build"
KIPR_ROBOT_IP="192.168.125.1"
KIPR_ROBOT_USER="kipr"
KIPR_ROBOT_PASS="botball"
DEPLOY_DIR="/home/kipr/comp"
SRC_DIR="$BASE_DIR/src" 

cd "$BASE_DIR/.."
sudo rm -rf "$BUILD_DIR"
sleep 0.1 

# Create build directory with proper permissions
sudo mkdir -p "$BUILD_DIR"
sudo chmod 777 "$BUILD_DIR"
sleep 0.1 

sshpass -p "$KIPR_ROBOT_PASS" scp \
    "scripts/values.txt" \
    "$KIPR_ROBOT_USER@$KIPR_ROBOT_IP:$DEPLOY_DIR"

sleep 0.1

echo "" 