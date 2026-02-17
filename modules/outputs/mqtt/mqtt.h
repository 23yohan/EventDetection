#pragma once

#include <mqtt/async_client.h>
#include<config.h>

enum ErrorMessages
{
    SUCCESSFUL,
    ERROR
};

class Mqtt
{
private:

    std::string _broker;
    std::string _clientID;
    std::string _topic;
    int _qos;
    int _timeout;
    int _port;
    int _maxRetries;
    bool _retain;

    mqtt::async_client* _client;
    mqtt::connect_options _options;

public:
    Mqtt(mqttParam params);
    ~Mqtt();

    bool connect_mqtt();
    int subscribe(std::string topic);
    int publish(std::string payload, std::string topic);
    int disconnect();
};
