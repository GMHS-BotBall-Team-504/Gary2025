# 🚀 Gary, 25' Spring

![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)
![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)

## 🌟 Overview
This project is designed for **BotBall**, a robotics competition, leveraging the **KIPR Wombat** platform. It includes functionality for controlling servos, motors, and sensors to perform various tasks such as object manipulation and movement.

> **Note**: This repository is intended to help other teams learn advanced programming techniques and enhance their own robots.

## 📂 Project Structure
- **`src/`**: Main source code files for the project.
- **`include/`**: Header files defining structures, constants, and function prototypes.
- **`scripts/`**: Scripts for compiling and uploading the program.
- **`develop/`**: Temporary development files.
- **`execution/`**: Final executable files after compilation.

## ✨ Key Features
- **🔧 Servo Control**: Gradual and synchronized servo movements using threads.
- **⚙️ Motor Control**: Precise translational and rotational movements.
- **📡 Sensor Integration**: Utilizes analog and digital sensors for feedback and control.
- **🧵 Multithreading**: Implements multithreaded operations for concurrent tasks.


## 📚 Dependencies
 - ```sshpass``` : Sends files over much easier and quickly
 - Docker: Used for cross-compilation.
 - CMake: Build system generator.
 - Ninja: Build system.

## 🛠️ How to Build
1. Install the above dependencies. 
2. Make sure the ```scripts``` folder is in the root directory of your project.  
3. Run the following script to build the project:
   ```sh
   ./scripts/compile.sh
    ```

## 📬 Contact
For questions or feedback, feel free to reach out:
- **Email**: trisonli0809@gmail.com
- **GitHub**: [Steam09](https://github.com/Steam09)
- **Discord**: monitor1509

## 📜 License
This project is licensed under the MIT License. See the LICENSE file for more details.

