# Real-Time Event Detection and Telementry System

The goal of this project is to montior real time detection of objects within a camera feed. The data is then aggregated and sent to a database & is publshed on MQTT topics.

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