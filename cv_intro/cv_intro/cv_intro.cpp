// cv_intro.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <opencv2/core/core.hpp>           // cv::Mat
#include "opencv2/highgui.hpp"
#include <opencv2/imgcodecs/imgcodecs.hpp>     // cv::imread()
#include <opencv2/imgproc/imgproc.hpp>     // cv::Canny()

#include "cv_imgproc.h"
#include "cv_facetrack.h"

using namespace std;
using namespace cv;


int main(int argc, char** argv) {
	//loadImgDemo("going-merry.png");
	//blurImgDemo("going-merry.png");
	//loadVideoDemo("flame.avi");
	//initCameraStream();
	//runBackgroundSub("flame.avi");
	detectEdgeCanny("dashcam.png");
	detectEdgeLaplacian("dashcam.png");
}
