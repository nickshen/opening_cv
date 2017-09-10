// cvintro.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
#include <opencv2/core/core.hpp>           // cv::Mat
#include "opencv2/highgui.hpp"
#include <opencv2/imgcodecs/imgcodecs.hpp>     // cv::imread()
#include <opencv2/imgproc/imgproc.hpp>     // cv::Canny()

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat imgMat = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file
	cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
	cv::resize(imgMat, imgMat, cv::Size(), 0.75, 0.75);
	imshow("Example1", imgMat);
	cvWaitKey(0);
	cvDestroyWindow("Example1");
}

