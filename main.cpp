#include <iostream>
#include "mqtt/async_client.h"

#include <config.h>
#include <mqtt.h>
using namespace std;


int main()
{
    std::cout << "Hello World" << std::endl;
    Config config("local.yaml");
    struct mqttParam params = config.get_mqtt_param();

    // Now lets create an mqtt instance
    Mqtt mqttObj(config.get_mqtt_param());
    bool successCon = mqttObj.connect_mqtt();
    if (successCon)
    {
        // int subSuc = mqttObj.subscribe("test/topic");
        int pubSuc = mqttObj.publish("Hellow from matthew", "test/topic");
        (pubSuc == 0) ? std::cout << "Success" << std::endl : std::cout << "Success failed" << std::endl;
    }
    else 
    {
        std::cout << "FAILURE (pls no)" << std::endl;
    }
    

    
    return 0;

}