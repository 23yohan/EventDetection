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
    int _minContourArea = 500;
    int _maxContourArea = 5000;

    cv::Mat _currentFrame;
    cv::Mat _previousFrame;
    cv::Mat _mask;
    std::vector<cv::Rect> _detections;
    cv::Mat _motionFrame;

public:
    ImageProcessing(struct imageConfig conf);
    ~ImageProcessing();

    void process_frame(cv::Mat frame, cv::Mat& dest);
    void load_image(std::string filePath, cv::Mat& dest);
    void create_motion_mask();
    void compute_contour_detection();
    void detect_motion(cv::Mat& currentFrame);
    void draw_detection();
    cv::Mat get_motion_frame();
    cv::Mat get_mask();
    void display_frames();

    std::vector<cv::Rect> get_detections();
};


