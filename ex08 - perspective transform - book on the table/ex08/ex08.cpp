// ex08.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {

	cv::Mat image;

	// read the image and display it
	// cv::IMREAD_UNCHANGED - image is read “as is”, color or grayscale
	image = cv::imread("../../img/book_perspective.png", cv::IMREAD_UNCHANGED);

	// always check if the image was successfully read!!!
	if (image.empty()) return -1;

	// Define original point positions and their coordinates in transformed image
	cv::Point2f srcQuad[] = {
		cv::Point2f(390, 232) , // src Top left
		cv::Point2f(663,375) ,  // src Top right
		cv::Point2f(393,744) ,  // src Bottom right
		cv::Point2f(87,503)     // src Bottom left
	};

	// label the points in the source image
	for (int i = 0; i < 4; i++)
		cv::circle(image, srcQuad[i], 5, cv::Scalar(255, 0, 255), -1, cv::LINE_AA);

	// Define the coordinates of the source points in the transformed destination image
	cv::Point2f dstQuad[] = {
		cv::Point2f(0, 0) , // src Top left
		cv::Point2f(image.cols - 1, 0) , // src Top right
		cv::Point2f(image.cols - 1, image.rows - 1) , // src Bottom right
		cv::Point2f(0, image.rows - 1) // src Bottom left
	};

	// Compute perspective transform (cv::getPerspectiveTransform)
	cv::Mat trans_matrix = cv::getPerspectiveTransform(srcQuad, dstQuad);

	cv::Mat dst;
	// Apply perspective matrix and warp the image
	cv::warpPerspective(image, dst, trans_matrix, image.size());

	// label the points in the destination image
	for (int i = 0; i < 4; i++)
		cv::circle(dst, dstQuad[i], 5, cv::Scalar(255, 0, 255), -1, cv::LINE_AA);

	// calculating size of window to show two image
	cv::Mat matWindow(cv::Size(image.cols * 2, image.rows), image.type(), cv::Scalar::all(0));
	cv::Mat img_tmp;

	// copy input image to window matrix
	img_tmp = matWindow(cv::Rect(0, 0, image.cols, image.rows));
	image.copyTo(img_tmp);

	// copy transformed image to window matrix
	img_tmp = matWindow(cv::Rect(image.cols, 0, image.cols, image.rows));
	dst.copyTo(img_tmp);

	// reshow original and transformed image
	cv::namedWindow("Original and Transformed image", cv::WindowFlags::WINDOW_AUTOSIZE);
	cv::imshow("Original and Transformed image", matWindow);

	// to keep the window open we use waitKey(msdelay), 0 is forever
	cv::waitKey();

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
