#pragma once

class ImageWrapper
{
	public:
	ImageWrapper(int width, int height);
	virtual ~ImageWrapper();
	ImageWrapper(const ImageWrapper&other);
	ImageWrapper& operator=(const ImageWrapper& other);
	ImageWrapper(ImageWrapper&& other);
	ImageWrapper& operator=(ImageWrapper&& other);
	
	int getImageSize();
	unsigned char * getData();
	
	private:
		int m_imageSize = 0;
		unsigned char *m_p = NULL;
};
