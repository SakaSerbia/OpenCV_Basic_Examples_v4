// ex01.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <opencv2/highgui.hpp>
//image I/O, window display and many other functions

int main(int argc, char** argv) {

	// initimage and window variables
	cv::Mat image;cv::namedWindow("figure", cv::WINDOW_AUTOSIZE);

	// read the image and display it
    // cv::IMREAD_UNCHANGED - image is read “as is”, color or grayscale
	image = cv::imread("../lena.jpg", cv::IMREAD_UNCHANGED); 

	// always check if the image was successfully read!!!
	if (image.empty()) return -1;  

	// show image; the window is selected through is unique name
	cv::imshow("figure", image); 

	// to keep the window open we use waitKey(msdelay), 0 is forever
	cv::waitKey(0);

	// after any button is pressed close the window and finish
	cv::destroyWindow("figure");

	return 0;
}
