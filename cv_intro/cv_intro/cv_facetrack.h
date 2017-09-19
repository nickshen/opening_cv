#pragma once
//cv_facetrack
int initCameraStream();
void runBackgroundSub(char* fileName);
void processVideo(char* videoFilename);
void processImages(char* firstFrameFilename);
