#pragma once

#include <string>
#include <yaml-cpp/yaml.h>

struct mqttParam
{
    std::string _broker;
    std::string _clientID;
    std::string _topic;
    int _qos;
    int _timeout;
    int _port;
    int _maxRetries;
    bool _retain;
};

class Config
{
private:
    //The YAML node
    YAML::Node _config;

    //Parsed Values
    struct mqttParam _mqttConfig;
    

public:
    Config(std::string filePath);

    // Get and set functions
    struct mqttParam get_mqtt_param();

    // Parser
    void parser();

    // setters
    std::string set_topic();

    ~Config();
};