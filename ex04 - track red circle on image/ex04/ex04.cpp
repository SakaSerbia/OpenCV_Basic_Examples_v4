// ex04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv) {

	// notice here that we are using the Opencv's embedded "String" class
	std::vector<cv::String> filenames;

	// again we are using the Opencv's embedded "String" class
	cv::String folder = "../../img/circle";

	// makes the list of files from specified folder
	cv::glob(folder, filenames);

	// logged object positions
	//std::vector<cv::Point2i> objCenter; 

	//cv::namedWindow("color", cv::WINDOW_AUTOSIZE);

	for (size_t i = 0; i < filenames.size(); ++i) {
		cv::Mat inImage = cv::imread(filenames[i]);

		if (!inImage.data) {
			std::cerr << "Problem loading image!!!" << std::endl;
		}
		// image is loaded
		//cv::imshow("color", inImage);

		// threshold the image, keep only the selected pixels
		cv::Mat selectedColor;
		cv::inRange(inImage, cv::Scalar(140, 140, 240), cv::Scalar(180, 180, 255), selectedColor);

		//cv::namedWindow("Selected color");
		//cv::imshow("Selected color", selectedColor);

		cv::GaussianBlur(selectedColor, selectedColor, cv::Size(9, 9), 2, 2);

		//cv::namedWindow("Blur image");
		//cv::imshow("Blur image", selectedColor);

		cv::Canny(selectedColor, selectedColor, 80, 230);

		cv::namedWindow("Canny");
		cv::imshow("Canny", selectedColor);

		// find contours
		std::vector<std::vector<cv::Point> > contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::findContours(selectedColor, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

		// find moments of the image
		cv::Moments m = cv::moments(selectedColor, true);
		cv::Point p(m.m10 / m.m00, m.m01 / m.m00);

		// print coordinates of center
		//std::cout << cv::Mat(p) << std::endl;
		std::cout << "[ " << p.x << ", " << p.y << " ]" << std::endl;

		// drawing the circle with calculated centar
		cv::circle(inImage, p, 75, cv::Scalar(128, 0, 0), 5, 8, 0);

		// show the resultant image with draw circle
		cv::namedWindow("Tracked red circle");
		cv::imshow("Tracked red circle", inImage);

		cv::waitKey(0);
	}

	cv::destroyAllWindows();

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
