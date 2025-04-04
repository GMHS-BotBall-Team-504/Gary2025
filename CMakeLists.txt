cmake_minimum_required(VERSION 3.10)
project(Spring2025Project C)

add_executable(botball_user_program)

# Specify the C standard
set(CMAKE_C_STANDARD 99)

# Specify gcc VERSION
set(CMAKE_C_COMPILER "aarch64-linux-gnu-gcc")

# Compiler flags
string(APPEND CMAKE_C_FLAGS " -g")
string(APPEND CMAKE_C_FLAGS " -Wall")

# Add all source files from the src directory
target_sources(botball_user_program
    PRIVATE
        src/main.c
        src/ports.c
        src/positions.c
        src/servos.c
        src/tasks.c
        src/threads.c
        src/translation.c
)

# Define the output executable
set(OUTPUT_EXECUTABLE botball_user_program)

# Link required libraries properly
target_link_libraries(botball_user_program
    PRIVATE
        kipr
        m
        z
        pthread
)
