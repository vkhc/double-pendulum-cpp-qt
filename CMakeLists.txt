cmake_minimum_required(VERSION 3.8)

set(PROJECT DoublePendulum)

project(${PROJECT} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set variabless
set(MAIN "${PROJECT}_Executable")

# Set path to qt6
set(QT_CONFIG_PATH "/home/vk/Qt/6.1.1/gcc_64/lib/cmake")
list(APPEND CMAKE_PREFIX_PATH ${QT_CONFIG_PATH})

# Find required Qt libraries
find_package(Qt6 REQUIRED COMPONENTS Widgets
                                     Gui)

set(CMAKE_EXE_LINKER_FLAGS -no-pie) # Without this wont run as exe on linux 


add_subdirectory(${PROJECT_SOURCE_DIR}/main)

