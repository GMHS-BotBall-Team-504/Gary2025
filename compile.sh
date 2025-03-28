#!/bin/bash

sudo cp -r include/ develop/
sudo cp -r src/ develop/
sudo docker run -it --rm --volume ./develop:/home/kipr:rw sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall src/*.c -lkipr -lm -o botball_user_program -lz -lpthread
cd develop/
sshpass -p "botball" scp botball_user_program kipr@192.168.125.1:/home/kipr/Documents/KISS/test
sudo cp botball_user_program ../execution
sudo rm -r *
cd ..
echo "Compiled sucessfully!"

exit 0