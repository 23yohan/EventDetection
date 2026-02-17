add_library(config_module
    config/config.cpp
) 

target_include_directories(config_module PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/config
)

target_link_libraries(config_module PUBLIC yaml-cpp)