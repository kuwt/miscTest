#include "imageWrapper.h"

// constructor
ImageWrapper::ImageWrapper(int width, int height)
{
	m_imageSize = width * height;
	m_p = new unsigned char[m_imageSize];
}

// destructor
ImageWrapper::~ImageWrapper()
{
	if (m_p)
	{
		delete[] m_p;
	}
	m_p = NULL;
}
// copy constructor
ImageWrapper::ImageWrapper(const ImageWrapper& other)
{
	m_imageSize = other.m_imageSize;
	m_p = new unsigned char[m_imageSize];
	for (int i = 0; i < m_imageSize; ++i)
	{
		m_p[i] = other.m_p[i];
	}
}
//move constructor
ImageWrapper::ImageWrapper(ImageWrapper&& other)
{
	m_imageSize = other.m_imageSize;
	m_p = other.m_p;

	other.m_p = NULL;
	other.m_imageSize = 0;
}

//assignment operator
ImageWrapper& ImageWrapper::operator=(const ImageWrapper& other)
{
	if (&other != this)
	{
		m_imageSize = 0;
		delete [] m_p;
		m_p = NULL;

		m_imageSize = other.m_imageSize;
		m_p = new unsigned char[m_imageSize];
		for (int i = 0; i < m_imageSize; ++i)
		{
			m_p[i] = other.m_p[i];
		}
	}
	return *this;
}

//move assignment operator
ImageWrapper& ImageWrapper::operator=(ImageWrapper&& other)
{
	if (&other != this)
	{
		m_imageSize = 0;
		delete[] m_p;

		m_imageSize = other.m_imageSize;
		m_p = other.m_p;

		other.m_p = NULL;
		other.m_imageSize = 0;
	}
	return *this;
}


int ImageWrapper::getImageSize()
{
	return m_imageSize;
}
unsigned char * ImageWrapper::getData()
{
	return m_p;
}