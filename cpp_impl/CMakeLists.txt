cmake_minimum_required(VERSION 3.10)
project(RoboticArmCPP)

# Use C++ 17 standard (Modern C++)
set(CMAKE_CXX_STANDARD 17)

# Find the SFML library (Graphics, Windowing, System)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Define our source files
add_executable(RobotArm 
    main.cpp 
    Arm.cpp 
)

# Link SFML to our executable
target_link_libraries(RobotArm sfml-graphics sfml-window sfml-system)