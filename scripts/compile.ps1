Set-Location ..
docker build -t gary2025 .
docker create --name gary2025 gary2025
docker start gary2025
docker cp gary2025:/root/build/build/botball_user_program ${PWD}/output
Set-Location scripts