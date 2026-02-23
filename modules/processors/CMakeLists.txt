add_library(config_module
    config/config.cpp
) 

add_library(image_processor_module
    image_processing/image_processor.cpp
)

target_include_directories(config_module PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/config
)

target_include_directories(image_processor_module PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/image_processing
)

target_link_libraries(image_processor_module PUBLIC ${OpenCV_LIBS} config_module)
target_link_libraries(config_module PUBLIC yaml-cpp)