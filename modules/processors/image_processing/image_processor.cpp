#include <opencv2/opencv.hpp>
#include <image_processor.h>

#define MAX_PIXEL_THRESHOLD 255

ImageProcessing::ImageProcessing(struct imageConfig conf)
{
    _dimensionX = conf._dimensionX;
    _dimensionY = conf._dimensionY;
    _threshold = conf._threshold;
    _blurSize = conf._blurSize;
    _kernelSize = conf._kernelSize;

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

    // Using a guassian blur for better smoothing and reduction of false positives
    cv::GaussianBlur(frameDiff, frameDiff, cv::Size(_blurSize, _blurSize), 0);
    cv::threshold(frameDiff, mask, 25, MAX_PIXEL_THRESHOLD,cv::THRESH_BINARY);

    // perform some morphology to remove some extra noise while keeping image binary.
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(_kernelSize,_kernelSize));
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel); //removes background noise (removes white spots in black areas)
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel); // removes black spots in white areas

    _mask = mask;
}

void ImageProcessing::detect_motion(cv::Mat& currentFrame)
{
    //update class members 
    _previousFrame = _currentFrame.clone();
    _currentFrame = currentFrame.clone();

    if (_previousFrame.empty())
    {
        return;
    }

    ImageProcessing::create_motion_mask();
}
