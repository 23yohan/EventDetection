add_library(mqtt_module
    mqtt/mqtt.cpp
)

target_include_directories(mqtt_module PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/mqtt
)

target_link_libraries(mqtt_module PUBLIC config_module) # MQTT depends on the config module