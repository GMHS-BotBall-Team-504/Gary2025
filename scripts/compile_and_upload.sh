#!/bin/bash
cd ..
rm -r out/build
mkdir out/build
cp -r include\ out/build
cp -r -Recurse src\ out/build
docker run -it --rm --volume ./out/build:/home/kipr:rw sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall -pthread src/main.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c -lkipr -lm -o botball_user_program
cd scripts
sshpass -p "botball" scp ./out/build/botball_user_program kipr@192.168.137.253:/home/kipr/botball_user_program
