#include <string>
#include <iostream>
#include <filesystem>
#include <yaml-cpp/yaml.h>
#include "config.h"

Config::Config(std::string fileName)
{
    // Relative from the exec
    std::string filePath = "../config/" + fileName;
    
    // Check if file exists 
    if (!std::filesystem::exists(filePath))
    {
        throw std::runtime_error("Config File not found: " + filePath);
    }

    // Create and assign the YAML file
    _config = YAML::LoadFile(filePath);
    Config::parser();
}

Config::~Config(){};

void Config::parser()
{
    // Get system requirements
    _sysConfig._osType = _config["system"]["os"].as<std::string>(); 
    
    // Get MQTT stuff
    _mqttConfig._broker     = _config["mqtt"]["broker"].as<std::string>();
    _mqttConfig._port       = _config["mqtt"]["port"].as<int>();
    _mqttConfig._clientID   = _config["mqtt"]["client_id"].as<std::string>();
    _mqttConfig._timeout    = _config["mqtt"]["timeout"].as<int>();
    _mqttConfig._retain     = _config["mqtt"]["retain"].as<bool>();
    _mqttConfig._qos        = _config["mqtt"]["qos"].as<int>();
    _mqttConfig._topic      = _config["mqtt"]["topic"].as<std::string>();
    _mqttConfig._maxRetries = _config["mqtt"]["max_retries"].as<int>();

    // Get camera stuff
    _camConfig._deviceID = _config["camera"]["device_id"].as<std::string>();
    _camConfig._devicePath = _config["camera"]["device_path"].as<std::string>(); 
    _camConfig._timeout = _config["camera"]["timeout"].as<int>();
    // We also want to store the system type so we can handle the device path accordingly
    _camConfig._systemOS = _sysConfig._osType;

    // Get image stuff
    _imgConfig._dimensionX = _config["image"]["dimensions"][0].as<int>();
    _imgConfig._dimensionY = _config["image"]["dimensions"][1].as<int>();
    _imgConfig._threshold = _config["image"]["threshold"].as<int>();
    _imgConfig._blurSize = _config["image"]["blurSize"].as<int>();
    _imgConfig._kernelSize = _config["image"]["kernelSize"].as<int>();
        
}

struct mqttParam Config::get_mqtt_param() { return _mqttConfig; }
struct cameraParam Config::get_camera_param() { return _camConfig; }
struct imageConfig Config::get_image_param() { return _imgConfig; }