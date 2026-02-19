add_library(camera_module
    usb_camera/usb_camera.cpp
)

target_include_directories(camera_module PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/usb_camera
)

target_link_libraries(camera_module PUBLIC 
    config_module
    ${OpenCV_LIBS}
) # Camera depends on the config module