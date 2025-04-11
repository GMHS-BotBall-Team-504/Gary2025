cd ..
Remove-Item -Recurse out/build
mkdir out/build
Copy-Item -Recurse include\ out/build
Copy-Item -Recurse src\ out/build
docker run -it --rm --volume D:\source\Gary2025\out\build:/home/kipr:rw sillyfreak/wombat-cross aarch64-linux-gnu-gcc -g -Wall -pthread src/main.c src/ports.c src/positions.c src/servos.c src/tasks.c src/threads.c src/translation.c -lkipr -lm -o botball_user_program
cd scripts