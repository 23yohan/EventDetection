#pragma once

#include <opencv2/opencv.hpp>
#include <config.h>



struct motionMetrics
{
  int changedPixels;
  int contourCount;
  double largestContourArea;  
};

class ImageProcessing
{
private:
    
    int _dimensionX;
    int _dimensionY;
    int _threshold;
    int _blurSize;
    int _kernelSize;

    cv::Mat _currentFrame;
    cv::Mat _previousFrame;
    cv::Mat _mask;

public:
    ImageProcessing(struct imageConfig conf);
    ~ImageProcessing();

    void process_frame(cv::Mat frame, cv::Mat& dest);
    void motion_detection();
    void load_image(std::string filePath, cv::Mat& dest);
    void create_motion_mask();
    void detect_motion(cv::Mat& currentFrame);
};


