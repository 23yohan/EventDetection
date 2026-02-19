#include <usb_camera.h>
#include <opencv2/opencv.hpp>

Camera::Camera(struct cameraParam param)
{
    _deviceID = param._deviceID;
    _devicePath = param._devicePath;
    _timeout = param._timeout;
    _systemOS = param._systemOS;

    _isCameraOpen = false;

    // .compare returns 0 so might need to just do it using ==?
    if (!_systemOS.compare("mac"))
    {
        _deviceIdx = Camera::find_camera();
        if (_deviceIdx < 0)
        {
            throw std::runtime_error("Camera Device does not exist: " + std::to_string(_deviceIdx));
        }
    }
    std::cout << "Camera initalisation successful" << std::endl;
}

int Camera::find_camera()
{
    // Function finds camera index on Mac
    for (int i = 0; i < 10; ++i)
    {
        cv::VideoCapture cap(i);
        if (cap.isOpened())
        {
            cap.release();
            return i;
        }
    }
    return -1;
}

void Camera::open_camera()
{
    if (!_cam.isOpened())
    {
        // Use openCV module to open camera
        // Check if you are opening a camera on MAC or not
        if (_systemOS == "mac")
        {
            _cam.open(_deviceIdx);
        }
        else
        {
            _cam.open(_devicePath);
        }
    }

}

void Camera::close_camera()
{
    if (_cam.isOpened())
    {
        _cam.release();
    }
}

bool Camera::check_camera_status()
{
    return _cam.isOpened();
}

bool Camera::take_image(cv::Mat& dest)
{
    Camera::open_camera(); // handles if camera is open or not
    return _cam.read(dest);
}


Camera::~Camera(){}