#include "DetectNumbers.h"

#include <string>

int main()
{
	namespace T = cvTech; 
	std::string path("/home/vardan/opencv_cods/opencv_tesseract/index.png");
	T::cvDetection* d = new T::cvDetection(path, 100, 200 );
	assert(d != 0);
	cv::Mat dst;
	cv::Mat img = d->cvGetImage();
	IplImage cp = img; 
	IplImage* sm = d->cvCopySourceImage(&cp);
	assert(sm != 0);
	cv::Mat m(sm);
	d->cvConverteToSmooth(m, 3, 3);
	IplImage* gray = d->cvCvtColors();
	IplImage* binary = d->cvBinarizeImage(&cp, gray);
	IplImage* tr = d->cvTransformImageEx(gray, binary, 10);
	assert(tr != 0);
	IplImage* canny = d->cvTrnasformToCanny(tr, gray, 100, 500, 3);
	assert(canny != 0);
	d->cvFindContoursInToImage(binary);
	d->show();
	if(d != 0)
	{
		delete d;
	}

	return 0;
}
