#include <opencv2/opencv.hpp>
#include <image_processor.h>

#define MAX_PIXEL_THRESHOLD 255

ImageProcessing::ImageProcessing(struct imageConfig conf)
{
    _dimensionX = conf._dimensionX;
    _dimensionY = conf._dimensionY;
    _threshold = conf._threshold;
    _blurSize = conf._blurSize;

    // Maybe some more stuff here
}

ImageProcessing::~ImageProcessing() {}

void ImageProcessing::process_frame(cv::Mat frame, cv::Mat& dest)
{
    // Convert the image to grayscale
    cv::Mat tempFrame;
    cv::cvtColor(frame, tempFrame, cv::COLOR_RGB2GRAY);

    // Add some blurring to the image
    cv::blur(tempFrame, dest, cv::Size(5,5));
}

void ImageProcessing::load_image(std::string filePath, cv::Mat& dest)
{
    dest = cv::imread(filePath);
    
    // for testing we will put it here
    cv::Mat res;
    ImageProcessing::process_frame(dest, res);
}

void ImageProcessing::create_motion_mask()
{
    cv::Mat frameDiff, mask;
    cv::Mat greyPrev, greyCur;

    cv::cvtColor(_previousFrame, greyPrev, cv::COLOR_RGB2GRAY);
    cv::cvtColor(_currentFrame, greyCur, cv::COLOR_RGB2GRAY);

    cv::absdiff(greyCur, greyPrev, frameDiff);

    // Use median blur to complete edge detection of objects
    cv::medianBlur(frameDiff, frameDiff, _blurSize);

    cv::threshold(frameDiff, mask, 25, MAX_PIXEL_THRESHOLD,cv::THRESH_BINARY);

    cv::medianBlur(mask, mask, _blurSize);

    cv::Mat kernel = cv::Mat::ones(cv::Size(5,5), CV_32F);
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);

    cv::imshow("Frame mask", mask);
    cv::waitKey(0);


}

void ImageProcessing::detect_motion(cv::Mat& currentFrame)
{
    //update class variables 
    _previousFrame = _currentFrame.clone();
    _currentFrame = currentFrame.clone();

    if (_previousFrame.empty())
    {
        return;
    }

    ImageProcessing::create_motion_mask();
}
