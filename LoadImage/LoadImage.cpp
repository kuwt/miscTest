#include "LoadImage.h"
#define ERROR (-1)
#define OK (0)

cv::Mat loadImage(const std::string& name)
{
	cv::Mat image = loadImage(name, CV_LOAD_IMAGE_GRAYSCALE);
	return image;
}

cv::Mat loadImage(const std::string& name, int mode)
{
	cv::Mat image = cv::imread(name, mode);
	;
	if (image.empty())
	{
		std::cerr << "Can't load image - " << name << std::endl;
		exit(-1);
	}
#if DEBUG
	cv::imshow(name, image);
	cv::waitKey(1);
#endif
	return image;
}

int loadImage(const std::string& name, int mode, cv::Mat &image)
{
	image = cv::imread(name, mode);

	if (image.empty())
	{
		std::cerr << "Can't load image - " << name << std::endl;
		return ERROR;
	}
#if DEBUG
	cv::imshow(name, image);
	cv::waitKey(1);
#endif
	return OK;
}
