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

struct cameraParam
{
    std::string _deviceID;
    std::string _devicePath;
    std::string _systemOS; // we handle camera set up for different paths
    int _timeout;

};

struct systemParam
{
    std::string _osType;
};

struct imageConfig
{
    int _dimensionX;
    int _dimensionY;
    int _threshold;
    int _blurSize;

    // More parameters
};

class Config
{
private:
    //The YAML node
    YAML::Node _config;

    //Parsed Values
    struct mqttParam _mqttConfig;
    struct cameraParam _camConfig;
    struct systemParam _sysConfig;
    struct imageConfig _imgConfig;
    

public:
    Config(std::string filePath);

    // Get and set functions
    struct mqttParam get_mqtt_param();
    struct cameraParam get_camera_param();
    struct imageConfig get_image_param();

    // Parser
    void parser();

    // setters
    std::string set_topic();

    ~Config();
};