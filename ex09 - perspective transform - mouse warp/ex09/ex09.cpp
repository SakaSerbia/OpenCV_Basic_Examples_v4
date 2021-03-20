// ex09.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat src;
cv::Mat dst;

cv::Point2f srcQuad[] = {
		cv::Point2f(390, 232), // src Top left
		cv::Point2f(663,375) , // src Top right
		cv::Point2f(393,744) , // src Bottom right
		cv::Point2f(87,503)    // src Bottom left
};

cv::Point2f dstQuad[4];
int selected_region = -1;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
		if (x < src.cols / 2)
		{ // left
			if (y < src.rows / 2)
			{ // up
				dstQuad[0] = cv::Point2f(x, y); // src Top left
				selected_region = 0;
			}
			else
			{ // down
				dstQuad[3] = cv::Point2f(x, y); // src Top left
				selected_region = 3;
			}
		}
		else
		{ // right
			if (y < src.rows / 2)
			{ // up
				dstQuad[1] = cv::Point2f(x, y); // src Top left
				selected_region = 1;
			}
			else
			{ //down
				dstQuad[2] = cv::Point2f(x, y); // src Top left
				selected_region = 2;
			}
		}
	}
	else if (event == cv::EVENT_RBUTTONDOWN)
	{
		selected_region = -1;
	}
	else if (event == cv::EVENT_MOUSEMOVE)
	{
		if (selected_region != -1) {
			dstQuad[selected_region] = cv::Point2f(x, y);

			cv::Mat trans_matrix = cv::getPerspectiveTransform(srcQuad, dstQuad);

			// Apply perspective matrix and warp the image
			cv::warpPerspective(src, dst, trans_matrix, src.size());

			// label the points in the destination image
			for (int i = 0; i < 4; i++)
				cv::circle(dst, dstQuad[i], 5, cv::Scalar(255, 0, 255), -1, cv::LINE_AA);

			cv::imshow("Transformed image", dst);
		}
	}

}

int main(int argc, char** argv) {

	// read the image and display it
	// cv::IMREAD_UNCHANGED - image is read “as is”, color or grayscale
	src = cv::imread("../../img/book_perspective.png", cv::IMREAD_UNCHANGED);

	// always check if the image was successfully read!!!
	if (src.empty()) return -1;

	cv::namedWindow("Original image", cv::WindowFlags::WINDOW_AUTOSIZE);

	// Define original point positions and their coordinates in transformed image

	// label the points in the source image
	for (int i = 0; i < 4; i++)
		cv::circle(src, srcQuad[i], 5, cv::Scalar(255, 0, 255), -1, cv::LINE_AA);

	cv::imshow("Original image", src);

	// Define the coordinates of the source points in the transformed destination image
	dstQuad[0] = cv::Point2f(0, 0); // src Top left
	dstQuad[1] = cv::Point2f(src.cols - 1, 0); // src Top right
	dstQuad[2] = cv::Point2f(src.cols - 1, src.rows - 1); // src Bottom right
	dstQuad[3] = cv::Point2f(0, src.rows - 1); // src Bottom left

	// Compute perspective transform (cv::getPerspectiveTransform)
	cv::Mat trans_matrix = cv::getPerspectiveTransform(srcQuad, dstQuad);

	// Apply perspective matrix and warp the image
	cv::warpPerspective(src, dst, trans_matrix, src.size());

	// label the points in the destination image
	for (int i = 0; i < 4; i++)
		cv::circle(dst, dstQuad[i], 5, cv::Scalar(255, 0, 255), -1, cv::LINE_AA);
	cv::imshow("Transformed image", dst);

	// set the callback function for any mouse event
	cv::setMouseCallback("Transformed image", CallBackFunc, NULL);

	// to keep the window open we use waitKey(msdelay), 0 is forever
	cv::waitKey();

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
