#!/bin/bash

sudo cp -r include/ develop/
sudo cp -r src/ develop/
sudo docker run -it --rm --volume ./develop:/home/kipr:rw sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall src/*.c -lkipr -lm -o botball_user_program -lz -lpthread
echo docker
cd develop/
sshpass -p "botball" scp botball_user_program kipr@10.0.0.250:/home/kipr/
echo sent
sudo cp botball_user_program ../execution
echo copied
sudo rm -r *
cd ..
echo "Compiled sucessfully!"
