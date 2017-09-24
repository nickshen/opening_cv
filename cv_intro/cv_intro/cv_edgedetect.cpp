#include "stdafx.h"
#include <iostream>

#include <opencv2/core/core.hpp>           // cv::Mat
#include <opencv2/highgui.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

#include "cv_imgproc.h"

using namespace std;
using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold = 80;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
const char* window_name = "Edge Map";

static void CannyThreshold(int, void*)
{
	blur(src_gray, detected_edges, Size(3, 3));
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
	dst = Scalar::all(0);
	src.copyTo(dst, detected_edges);
	imshow(window_name, dst);
}

int detectEdgeCanny(char* fileName)
{
	src = imread(fileName, IMREAD_COLOR); // Load an image
	if (src.empty())
	{
		return -1;
	}
	dst.create(src.size(), src.type());
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	namedWindow(window_name, WINDOW_AUTOSIZE);
	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
	CannyThreshold(0, 0);
	waitKey(0);
	return 0;
}

int detectEdgeLaplacian(char* fileName)
{
	Mat src, src_gray, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	const char* window_name = "Laplace Demo";
	String imageName = fileName;
	src = imread(imageName, IMREAD_COLOR); // Load an image
	if (src.empty())
	{
		return -1;
	}
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, COLOR_BGR2GRAY); // Convert the image to grayscale
	Mat abs_dst;
	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	imshow(window_name, abs_dst);
	waitKey(0);
	return 0;
}