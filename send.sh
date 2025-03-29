#!/bin/bash

sudo echo hi
./compile.sh
cd execution/
sshpass -p "botball" scp botball_user_program kipr@10.0.0.250:/home/kipr/Documents/KISS/test/
echo done
cd ..

exit 0