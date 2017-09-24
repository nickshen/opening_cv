#pragma once
int loadImgDemo(cv::String imgToLoad);
int blurImgDemo(cv::String imgToLoad);

//segmentation/background-subtraction
int loadVideoDemo(char* fileName);

//edge-detect
int detectEdgeCanny(char* fileName);
int detectEdgeLaplacian(char* fileName);