cd ..
Remove-Item -Recurse out/build
mkdir out/build
Copy-Item -Recurse include\ out/build
Copy-Item -Recurse src\ out/build
docker run -it --rm --volume D:\source\Gary2025\out\build:/home/kipr:rw sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall -pthread src/main.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c -lkipr -lm -o botball_user_program
cd scripts
scp -i "C:\Users\Conno\.ssh\id_ed25519" D:\source\Gary2025\out\build\botball_user_program kipr@192.168.137.253:/home/kipr/botball_user_program
ssh kipr@192.168.137.253 'chmod +x ~/botball_user_program'
ssh kipr@192.168.137.253 './botball_user_program'