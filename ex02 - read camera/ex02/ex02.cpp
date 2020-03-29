// ex02.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main(int argc, char** argv) {

	cv::namedWindow("frame", cv::WINDOW_AUTOSIZE);
	cv::VideoCapture cap;

	if (argc == 1) {
		// open the first camera
		cap.open(0);
	}
	else {
		// camera filename is given
		cap.open(argv[1]); 
	}

	if (!cap.isOpened()) { 
		// check if we succeeded
		std::cerr << "Couldn't open capture." << std::endl;
		return -1;
	}

	while (1) {

		cv::Mat frame, frame_gray, outFrame;

		if (cap.read(frame)) { 
			// if read was successful display the frame
			imshow("frame", frame);     

		}
		//delay 1ms
		char c = (char)cv::waitKey(1); 

		// if ESC was pressed, break
		if (c == 27) break; 
	}

	// close the camera feed and release camera
	cap.release(); 

}
