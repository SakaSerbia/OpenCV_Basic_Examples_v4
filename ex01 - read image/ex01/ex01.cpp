// ex01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{

	// initimage and window variables
	cv::Mat image; cv::namedWindow("figure", cv::WINDOW_AUTOSIZE);

	// read the image and display it
	// cv::IMREAD_UNCHANGED - image is read “as is”, color or grayscale
	image = cv::imread("../../img/lena.jpg", cv::IMREAD_UNCHANGED);

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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
