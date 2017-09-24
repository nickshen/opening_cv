#include "stdafx.h"
#include <iostream>

#include <opencv2/core/core.hpp>           // cv::Mat
#include "opencv2/highgui.hpp"
#include <opencv2/imgcodecs/imgcodecs.hpp>     // cv::imread()
#include <opencv2/imgproc/imgproc.hpp>     // cv::Canny()

#include "cv_imgproc.h"

using namespace std;
using namespace cv;

int DELAY_CAPTION = 1000;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;	//size of bounds to blur, changes AoE and amount of computation

Mat source; Mat dest;
char window_name[] = "Smoothing Demo";
int display_caption(const char* caption);
int display_dst(int delay);

//load and resize image
int loadImgDemo(cv::String imgToLoad)
{
	Mat imgMat = imread(imgToLoad, CV_LOAD_IMAGE_COLOR);   // Read the file
	cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
	cv::resize(imgMat, imgMat, cv::Size(), 0.75, 0.75);
	imshow("Example1", imgMat);
	cvWaitKey(0);
	cvDestroyWindow("Example1");
	return 0;
}

//four types of image blurring.. try this with video input later
int blurImgDemo(cv::String imgToLoad)
{
	namedWindow(window_name, WINDOW_AUTOSIZE);
	source = imread(imgToLoad, IMREAD_COLOR);
	cv::resize(source, source, cv::Size(), 0.75, 0.75);
	if (display_caption("Original Image") != 0) { return 0; }
	dest = source.clone();
	if (display_dst(DELAY_CAPTION) != 0) { return 0; }
	if (display_caption("Homogeneous Blur") != 0) { return 0; }
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		blur(source, dest, Size(i, i), Point(-1, -1));
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}

	if (display_caption("Gaussian Blur") != 0) { return 0; }
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		GaussianBlur(source, dest, Size(i, i), 0, 0);
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}

	if (display_caption("Median Blur") != 0) { return 0; }
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		medianBlur(source, dest, i);
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}

	if (display_caption("Bilateral Blur") != 0) { return 0; }
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		bilateralFilter(source, dest, i, i * 2, i / 2);
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}
	display_caption("End: Press a key!");
	waitKey(0);
	return 0;
}

int display_caption(const char* caption)
{
	dest = Mat::zeros(source.size(), source.type());
	putText(dest, caption,
		Point(source.cols / 4, source.rows / 2),
		FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
	imshow(window_name, dest);
	int c = waitKey(DELAY_CAPTION);
	if (c >= 0) { return -1; }
	return 0;
}

int display_dst(int delay)
{
	imshow(window_name, dest);
	int c = waitKey(delay);
	if (c >= 0) { return -1; }
	return 0;
}

//play video
int loadVideoDemo(char* fileName)
{
	char* windowName = "Example2";

	cvNamedWindow(windowName, CV_WINDOW_AUTOSIZE);
	CvCapture* capture = cvCreateFileCapture(fileName);
	IplImage* frame;
	while (1) {
		frame = cvQueryFrame(capture);
		if (!frame) break;
		cvShowImage(windowName, frame);
		char c = cvWaitKey(33);
		if (c == 27) break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow(windowName);

	return 0;
}

//next task: play video from input stream, apply median blur to every frame
//then.. apply 6 morphologies to 6 copies of input stream