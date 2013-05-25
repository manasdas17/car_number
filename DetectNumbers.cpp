
#include "DetectNumbers.h"

#include <cassert>

const char* wndname = "Detect Car Numbers";

cvTech::cvDetection::cvDetection(const std::string& str, int threshold, int maxvalue) :
	  mPath(str)
	, mThreshold(threshold)
	, mMaxValue(maxvalue)
{
	mImage = cv::imread(mPath, 1);
}

void cvTech::cvDetection::cvSetImagePath(const std::string& str)
{
	assert(!str.empty());
	mPath = str;
}

std::string cvTech::cvDetection::cvGetImagePath() const
{
	return mPath;
}

cv::Mat cvTech::cvDetection::cvGetImage() const
{
	return mImage;
}

int cvTech::cvDetection::cvGetThreshold() const
{
	return mThreshold;		
}

int cvTech::cvDetection::cvGetMaxValue() const
{
	return mMaxValue;
}

cvTech::cvDetection::cvDetection(const cvDetection& d)
{
	this->mPath = d.cvGetImagePath();
        this->mImage = d.cvGetImage();
	this->mThreshold = d.cvGetThreshold();
	this->mMaxValue = d.cvGetMaxValue();
}

cvTech::cvDetection& cvTech::cvDetection::operator=(const cvDetection& d)
{
	if(&d == this)
	{
		return (*this);
	}
	this->mPath = d.cvGetImagePath();
        this->mImage = d.cvGetImage();
	this->mThreshold = d.cvGetThreshold();
	this->mMaxValue = d.cvGetMaxValue();
	return (*this);
}


void cvTech::cvDetection::cvShowImage(const IplImage& im)
{
	cv::Mat temp;
    cvArrToMatrix(im, temp);
	imshow(wndname, temp);
	int c = cv::waitKey();
}

void cvTech::cvDetection::cvArrToMatrix(const IplImage& src, cv::Mat& m)
{
	m = cv::cvarrToMat(&src);
}

cv::Mat cvTech::cvDetection::cvConverteToSmooth(cv::Mat src, size_t w, size_t h)
{
	IplImage i = mImage;
	IplImage* img = cvCloneImage(&i);
	IplImage s = src;
	cvSmooth(&s, img, CV_GAUSSIAN, w, h);
	cv::Mat m(img);
	return m;
}

IplImage* cvTech::cvDetection::cvCreateNewImage(const IplImage* src, int depth, int a)
{
	IplImage* dst = cvCreateImage(cvSize(src->width, src->height), depth, 1);
	assert(dst != 0);
	return dst;
}

IplImage* cvTech::cvDetection::cvCopySourceImage(IplImage* src)
{
	IplImage* dst = cvCloneImage(src);
	assert(dst != 0);
	return dst;
}

IplImage* cvTech::cvDetection::cvTransformImageEx(IplImage* gray, IplImage* binary, size_t radius)
{
	assert(binary != 0);
	IplConvKernel* kern = cvCreateStructuringElementEx(radius*2, radius*2, radius, radius, CV_SHAPE_RECT);
	IplImage img = mImage;
	IplImage* temp = cvCreateImage(cvSize(img.width, img.height), img.depth, 1);
	IplImage* dst = cvCopySourceImage(gray);
	cvMorphologyEx(binary, dst, temp, kern, CV_MOP_TOPHAT,1);
	assert(dst != 0);
	return dst;
}

IplImage* cvTech::cvDetection::cvCvtColors()
{
	IplImage img = mImage;
	IplImage* gray = cvCreateImage(cvSize(img.width, img.height), 8, 1);
	IplImage* img1 = cvCopySourceImage(&img);
	cvCvtColor(img1, gray, CV_RGB2GRAY);
	assert(gray!=0);
	return gray;
}

IplImage* cvTech::cvDetection::cvBinarizeImage(const IplImage* src, IplImage* gray)
{
	IplImage img = mImage;
	IplImage* binary = cvCreateNewImage(src, img.depth, 1);
	cvThreshold(gray, binary, mThreshold, mMaxValue, CV_THRESH_BINARY);
	assert(binary != 0);
	return binary;
}

IplImage* cvTech::cvDetection::cvTrnasformToCanny(IplImage* morf, IplImage* gray, int a, int b, int c)
{
	IplImage* canny = cvCopySourceImage(gray);
	assert(morf != 0);
	assert(canny != 0);
	cvCanny(morf, canny, a, b, c);
	assert(canny != 0);
	return canny;
}

CvSeq* cvTech::cvDetection::cvFindContoursInToImage(IplImage* binary)
{
	CvSeq *ptr,*polygon;
	CvMemStorage *mem;
	mem = cvCreateMemStorage(0);
	CvSeq *contours = 0;
	IplImage img = mImage;
	cvFindContours(binary, mem, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
	for (ptr = contours; ptr != NULL; ptr = ptr->h_next) 
	{
		double reg = fabs(cvContourArea(ptr, CV_WHOLE_SEQ));
		if(reg >10 && reg <600)
		{
			cvApproxPoly(ptr, sizeof(CvContour), mem, CV_POLY_APPROX_DP, 3, 1);
			CvScalar ext_color = CV_RGB( 255, 255, 255 ); //randomly coloring different contours
			//cvDrawContours(&img, ptr, ext_color,CV_RGB(0,0,0), -1, CV_FILLED, 8, cvPoint(0,0));
			CvRect rectEst = cvBoundingRect( ptr, 0 );
			CvPoint pt1,pt2;
			pt1.x = rectEst.x;
			pt1.y = rectEst.y;
			pt2.x = rectEst.x+ rectEst.width;
			pt2.y = rectEst.y+ rectEst.height;
			int thickness =1 ;
			cvRectangle(&img, pt1, pt2, CV_RGB(80, 255, 0 ), thickness );
			cvResetImageROI(&img);
		}
	}
	assert(contours != 0);
	return contours;
}

void cvTech::cvDetection::show()
{
//	cv::Mat temp;
  //  cvArrToMatrix(*mImage, temp);
	imshow(wndname, mImage);
	int c = cv::waitKey();
}
