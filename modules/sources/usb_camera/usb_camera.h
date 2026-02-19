#pragma once

#include <opencv2/opencv.hpp>
#include <config.h>

class Camera
{
private:
    std::string _deviceID;
    std::string _devicePath; // Even if the device is on a mac, we can convert the string to an int
    int _deviceIdx;
    int _timeout;
    std::string _systemOS;

    bool _isCameraOpen;
    cv::VideoCapture _cam;

public:
    Camera(struct cameraParam param);
    ~Camera();
    int find_camera();
    void open_camera();
    void close_camera();
    bool check_camera_status();
    bool take_image(cv::Mat& dest);
};


