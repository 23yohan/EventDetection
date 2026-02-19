# Real-Time Event Detection and Telementry System

## Overview

This project is a modular real-time video processing system written in modern C++.

The goal of this project is to demonstrate the design and implementation of a long-running service that performs continous video monitoring, detects meaningful events, and publishes structured telementry to external systems.

This project will focus on modularity and reliable event generation, rather than machine learning accuracy. The intent is to model real-world edge environments where stability, reliablilty and maintainability are more important that raw computer vision performance

## Dependencies
- OpenCV: `brew install opencv` (macOS) or `sudo apt-get install libopencv-dev` (Linux)
- Paho MQTT: included as submodule
- yaml-cpp: included as submodule

## Installation

To ensure proper installation with the 3rd party libraries, the following can be done

```
git clone git@github.com:23yohan/EventDetection.git
cd dependencies

git submodule update
git submodule init

cd ..

mkdir build
cd build
cmake ..
````