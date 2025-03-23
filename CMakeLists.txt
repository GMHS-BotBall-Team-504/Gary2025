cmake_minimum_required(VERSION 3.10)
project(Spring2025Project C)

# Specify the C standard
set(CMAKE_C_STANDARD 99)

# Add all source files from the src directory
file(GLOB SRC_FILES src/*.c)

# Define the output executable
set(OUTPUT_EXECUTABLE botball_user_program)

# Custom command to use Docker for compilation
add_custom_target(
    ${OUTPUT_EXECUTABLE}
    COMMAND docker run -it --rm
            --volume ${CMAKE_SOURCE_DIR}/src:/home/kipr:rw
            --volume ${CMAKE_SOURCE_DIR}/develop:/home/develop:rw
            sillyfreak/wombat-cross
            aarch64-linux-gnu-gcc -Wall ${SRC_FILES} -lkipr -lm -o /home/develop/${OUTPUT_EXECUTABLE} -lz -lpthread
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building project using Docker"
)