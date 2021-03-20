// ex06.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>

// include file for every supported OpenCV function
#include <opencv2/opencv.hpp>

int main()
{

	// notice here that we are using the Opencv's embedded "String" class
	//std::vector<cv::String> filenames;

	// again we are using the Opencv's embedded "String" class
	//cv::String folder = "../img";

	// makes the list of files from specified folder
	//cv::glob(folder, filenames);

	// read input image
	cv::Mat inImage = cv::imread("../../img/logo.png");

	// test if image is read correctly; not empty
	if (inImage.empty()) {
		return -1;
	}

	// show image; the window is selected through is unique name
	//cv::namedWindow("Original image", cv::WindowFlags::WINDOW_AUTOSIZE);
	//cv::imshow("Original image", inImage);

	// transformed image declaration
	cv::Mat transImage;

	// calculating size of window to show two image
	cv::Mat matWindow(cv::Size(inImage.cols * 2, inImage.rows), inImage.type(), cv::Scalar::all(0));

	// copy input image to window matrix
	cv::Mat matRoi = matWindow(cv::Rect(0, 0, inImage.cols, inImage.rows));
	inImage.copyTo(matRoi);

	// define original point positions and their coordinates in transformed image
	cv::Point2f srcQuad[] = {
		cv::Point2f(0, 0) ,                               // src Top left
		cv::Point2f(inImage.cols - 1, 0) ,                // src Top right
		cv::Point2f(inImage.cols - 1, inImage.rows - 1) , // src Bottom right
		cv::Point2f(0, inImage.rows - 1)                  // src Bottom left
	};

	// define the coordinates of the source points in the transformed destination image
	cv::Point2f dstQuad[] = {
		cv::Point2f(inImage.cols * 0.05f, inImage.rows * 0.33f), // dst Top left
		cv::Point2f(inImage.cols * 0.9f, inImage.rows * 0.25f),  // dst Top right
		cv::Point2f(inImage.cols * 0.8f, inImage.rows * 0.9f),   // dst Bottom right
		cv::Point2f(inImage.cols * 0.2f, inImage.rows * 0.7f)    // dst Bottom left
	};

	// compute perspective transform (cv::getPerspectiveTransform)
	cv::Mat warpMat = cv::getPerspectiveTransform(
		srcQuad,  // coordinates of *four* vertices
		dstQuad   // target coords, four vertices
	);            // return 3-by-3 matrix

	// apply perspective matrix and warp the image
	cv::Mat dstImage;

	cv::warpPerspective(
		inImage,             // input image
		dstImage,            // result image
		warpMat,             // 3-by-3 transform mtx
		inImage.size(),      // destination image size
		cv::INTER_LINEAR,    // interpolation, inverse
		cv::BORDER_CONSTANT, // extrapolation method
		cv::Scalar()         // for constant borders
	);

	// label the points in the destination image
	for (int i = 0; i < 4; i++)
		cv::circle(dstImage, dstQuad[i], 5, cv::Scalar(255, 0, 255), -1, cv::LINE_AA);

	// copy transformed image to window matrix
	matRoi = matWindow(cv::Rect(inImage.cols, 0, inImage.cols, inImage.rows));
	dstImage.copyTo(matRoi);

	cv::imshow("Original and transformed image", matWindow);

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
