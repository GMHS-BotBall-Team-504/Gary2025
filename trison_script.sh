#!/bin/bash

sudo cp -r include/ develop/
sudo cp -r src/ develop/

sudo docker run -it --rm --volume ./develop:/home/kipr:rw sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall src/*.c -lkipr -lm -o botball_user_program -lz -lpthread

echo docker
cd develop/
# This is the check for either 10.0.0.250 or 192.168.125.1 or 192.168.124.1
sshpass -p "botball" scp botball_user_program kipr@192.168.125.1:/home/kipr
echo sent
sudo cp botball_user_program ../execution
echo copied
sudo rm -r *
cd ..
echo "Compiled sucessfully!"