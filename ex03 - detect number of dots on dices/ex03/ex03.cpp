// ex03.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

//using namespace std;

int main(int argc, char** argv) {

	// notice here that we are using the Opencv's embedded "String" class
	std::vector<cv::String> filenames;

	// again we are using the Opencv's embedded "String" class
	cv::String folder = "../../img/dices";

	// makes the list of files from specified folder
	cv::glob(folder, filenames);

	//cv::namedWindow("color", cv::WINDOW_AUTOSIZE);

	for (size_t i = 0; i < filenames.size(); ++i) {

		cv::Mat inImage = cv::imread(filenames[i]);

		if (!inImage.data) {
			std::cerr << "Problem loading image!!!" << std::endl;
		}

		// image is loaded
		// here goes your processing code -> detect dots on dices and count them

		// show image; the window is selected through is unique name
		//cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
		//cv::imshow("Original", inImage);

		// convert the source image from RGB to the destination grayscale image
		cv::Mat grayImage;
		cv::cvtColor(inImage, grayImage, cv::COLOR_BGR2GRAY);

		// show image; converted grayscale image
		//cv::namedWindow("Grayscale");
		//cv::imshow("Grayscale", grayImage);

		// blurring the image to reduces noise
		//cv::blur(grayImage, grayImage, cv::Size(3, 3));

		// show image; blurring grayscale image
		//cv::namedWindow("Blurring");
		//cv::imshow("Blurring", grayImage);

		// binary thresholding - if its value is greater than a threshold value, 
		// it is assigned maximum value (white, 255), else it is assigned minimum value (0, black):
		//cv::threshold(grayImage, grayImage, 170, 255, cv::THRESH_BINARY);

		// show image; blurring grayscale image
		//cv::namedWindow("Binary thresholding");
		//cv::imshow("Binary thresholding", grayImage);

		cv::Canny(grayImage, grayImage, 80, 230);

		//cv::namedWindow("Canny");
		//cv::imshow("Canny", grayImage);

		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::findContours(grayImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

		std::vector<cv::RotatedRect> diceRects;
		for (int i = 0; i < contours.size(); i++) {
			// for each contour, search the minimum area rectangle
			cv::RotatedRect rect = minAreaRect(contours[i]);

			// process only rectangles that are almost square and of the right size,
			// area size depends on image resolution
			float aspect = fabs(rect.size.aspectRatio() - 1);

			if ((aspect < 0.4) && (rect.size.area() > 100) && (rect.size.area() < 1200)) {

				// check if it's a duplicate rect
				bool process = true;

				for (int j = 0; j < diceRects.size(); j++) {
					float dist = norm(rect.center - diceRects[j].center);
					if (dist < 10) {
						process = false;
						break;
					}
				}

				if (process) {
					diceRects.push_back(rect);

					// draw square over original image
					cv::Point2f points[4];
					rect.points(points);
					for (int j = 0; j < 4; j++) {
						cv::line(inImage, points[j], points[(j + 1) % 4], cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
					}
				}
			}
		}

		// write result on screen
		char buffer[32];
		sprintf_s(buffer, "The result: %d", (int)diceRects.size());
		cv::putText(inImage, buffer, cv::Point(20, 30), cv::FONT_HERSHEY_DUPLEX, 0.8, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);

		cv::namedWindow("Counted dots");
		cv::imshow("Counted dots", inImage);

		// to keep the window open we use waitKey(msdelay), 0 is forever
		cv::waitKey(0);

	}

	// after any button is pressed close the window and finish
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
