// ex02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
