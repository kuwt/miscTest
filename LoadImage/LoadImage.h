#pragma once

#include <opencv2/opencv.hpp>

/*************************
Load as CV_LOAD_IMAGE_GRAYSCALE
**************************/
cv::Mat loadImage(const std::string& name);

/*************************
User specify the mode, e.g. CV_LOAD_IMAGE_GRAYSCALE
*************************/
cv::Mat loadImage(const std::string& name, int mode);

/*************************
// User specify the mode, e.g. CV_LOAD_IMAGE_GRAYSCALE
return status
*************************/
int loadImage(const std::string& name, int mode, cv::Mat &image);