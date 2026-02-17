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
    
    // Get MQTT stuff
    _mqttConfig._broker     = _config["mqtt"]["broker"].as<std::string>();
    _mqttConfig._port       = _config["mqtt"]["port"].as<int>();
    _mqttConfig._clientID   = _config["mqtt"]["client_id"].as<std::string>();
    _mqttConfig._timeout    = _config["mqtt"]["timeout"].as<int>();
    _mqttConfig._retain     = _config["mqtt"]["retain"].as<bool>();
    _mqttConfig._qos        = _config["mqtt"]["qos"].as<int>();
    _mqttConfig._topic      = _config["mqtt"]["topic"].as<std::string>();
    _mqttConfig._maxRetries = _config["mqtt"]["max_retries"].as<int>();
    
}

struct mqttParam Config::get_mqtt_param() { return _mqttConfig; }