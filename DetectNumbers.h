#ifndef DETECTNUMBERS_H
#define DETECTNUMBERS_H

#include <baseapi.h>
#include "opencv/cv.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <opencv2/opencv.hpp>
#include <string>

namespace cvTech
{
	class cvDetection;
}

class cvTech::cvDetection
{
	private:
		std::string mPath;
		int mThreshold;
		int mMaxValue;
		cv::Mat mImage;

	public:
 		virtual void cvShowImage(const IplImage& im);
		virtual void cvArrToMatrix(const IplImage& src, cv::Mat& m);
    	        virtual cv::Mat cvConverteToSmooth(cv::Mat s, size_t w, size_t h);
 		virtual IplImage* cvCreateNewImage(const IplImage* src, int depth, int a);
		virtual IplImage* cvCopySourceImage(IplImage* src);
		virtual IplImage* cvTransformImageEx(IplImage* gray, IplImage* binary, size_t radius);
		virtual IplImage* cvCvtColors();
		virtual IplImage* cvBinarizeImage(const IplImage* src, IplImage* gray);
		virtual IplImage* cvTrnasformToCanny(IplImage* morf, IplImage* gray, int a, int b, int c);
		virtual CvSeq* cvFindContoursInToImage(IplImage* binary);
		virtual void show();

	public:
		explicit cvDetection(const std::string& str, int threshold, int maxvalue);
		cvDetection(const cvDetection& d);
		cvDetection& operator=(const cvDetection& d);
		std::string cvGetImagePath() const;
		cv::Mat cvGetImage() const;
		void cvSetImagePath(const std::string& str);
		int cvGetThreshold() const;
		int cvGetMaxValue() const;
};

#endif // DETECTNUMBERS_H
