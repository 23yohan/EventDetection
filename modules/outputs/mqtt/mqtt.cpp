#include "mqtt/async_client.h"
#include <mqtt.h>

Mqtt::Mqtt(mqttParam params)
{
    // Populate class members
    _broker = params._broker;
    _clientID = params._clientID;
    _topic = params._topic;
    _qos = params._qos;
    _timeout = params._timeout;
    _port = params._port;
    _retain = params._retain;
    _maxRetries = params._maxRetries;

    // Build broker string
    std::string brokerStr = "tcp://" + _broker + ":" + std::to_string(_port);

    _client = new mqtt::async_client(brokerStr, _clientID);
    _options.set_keep_alive_interval(_timeout);
    _options.set_clean_session(true);

}

bool Mqtt::connect_mqtt()
{
    // Connect to client
    try 
    {        
        mqtt::token_ptr conTok = _client->connect(_options);
        conTok->wait();
        return _client->is_connected();
    }
    catch (const mqtt::exception &e)
    {
        std::cerr << "MQTT Connection failed: " << e.what() << std::endl;
        return false;
    }
}

int Mqtt::subscribe(std::string topic)
{
    for (int attempt = 0; attempt < _maxRetries; attempt++)
    {
        if (!_client->is_connected())
        {
            std::cerr << "Not Connected to MQTT broker. Attempt " << 
                attempt + 1 << " of " << _maxRetries << std::endl;
            
            Mqtt::connect_mqtt();
            continue;
        }

        // If we get here, we know that we are connected
        try {
            mqtt::token_ptr tok = _client->subscribe(topic, _qos);
            tok->wait(); // Wait until the subscription happens
            return ErrorMessages::SUCCESSFUL;
        }
        catch (const mqtt::exception &e)
        {
            std::cerr << "Error trying to subscribe to the topic " << topic << std::endl;
            return ErrorMessages::ERROR;
        }
    }
    // If we get here we know connnection failed so raise error
    std::cerr << "Unable to subscribe due to connection" << std::endl;
    // Look to maybe throwing exception here to handle back in the main
    return ErrorMessages::ERROR;

}

int Mqtt::publish(std::string payload, std::string topic)
{
    for (int attempt = 0; attempt < _maxRetries; attempt++)
    {
        if (!_client->is_connected())
        {
            std::cerr << "Not Connected to MQTT broker. Attempt " << 
                attempt + 1 << " of " << _maxRetries << std::endl;
            
            Mqtt::connect_mqtt();
            continue;
        }
        try {
                // Here we want to create a payload
                mqtt::message_ptr msg = mqtt::make_message(topic, payload, _qos, _retain);
                _client->publish(msg)->wait(); // We can wait on the message to be published
                return ErrorMessages::SUCCESSFUL;
        }
        catch (const mqtt::exception &e)
        {
            std::cerr << "Error trying to publish to the topic " << topic << std::endl;
            return ErrorMessages::ERROR;
        }
    }
    // If we get here we know connnection failed so raise error
    std::cerr << "Unable to publish due to connection" << std::endl;
    // Look to maybe throwing exception here to handle back in the main
    return ErrorMessages::ERROR;

}

int Mqtt::disconnect()
{
    try 
    {
        _client->disconnect();
        return ErrorMessages::SUCCESSFUL;
    }
    catch (const mqtt::exception &e)
    {
        std::cerr << "Unable to disconnect from MQTT broker" << std::endl;
        return ErrorMessages::ERROR;
    }
}

Mqtt::~Mqtt(){ delete _client;}