cmake_minimum_required(VERSION 3.20)
project(VideoEventSys)


# Set C++ Version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV Package
find_package(OpenCV REQUIRED)

# Set parameters for paho build
set(PAHO_WITH_MQTT_C ON CACHE BOOL "")
set(PAHO_BUILD_EXAMPLES ON CACHE BOOL "") # Probably dont need to build with examples
set(PAHO_BUILD_TESTS OFF CACHE BOOL "")

add_subdirectory(dependencies/paho.mqtt.cpp)
add_subdirectory(dependencies/yaml-cpp)
add_subdirectory(modules)


add_executable(app_c main.cpp)
target_link_libraries(app_c PRIVATE 
    config_module
    mqtt_module
    camera_module
    ${OpenCV_LIBS}
    paho-mqttpp3
    paho-mqtt3as
    yaml-cpp
)