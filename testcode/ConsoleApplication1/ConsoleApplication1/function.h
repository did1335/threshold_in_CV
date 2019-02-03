#pragma once

#include <iostream>
#include <cstdlib>
#include <opencv\cv.h>
#include <opencv2\highgui.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

//main.cpp
void create_trackbar();

//newWindow.cpp
void newWindow(String name);

//format.cpp
string int2String(int number);

//findrect.cpp
void findMinAreaRect(Mat &threshold_output);

//mix.cpp
void mix(String WindowName, Mat &a, double alpha, Mat &b, Mat &output);

