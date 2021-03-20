// ex07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat image, img_t, img_tmp;

cv::Mat matWindow;

int angle_slider = 0;

int cx_slider = 300;
int cy_slider = 400;

static void on_trackbar(int, void*) {

	// generate matrix rotation with arbitrary angle and center of rotation (cv::getRotationMatrix2D)
	cv::Mat rotation_matrix = cv::getRotationMatrix2D(cv::Point2f(cy_slider, cx_slider), angle_slider, 1);
	// implamate rotate matrix on transformed image (cv::warpAffine)
	cv::warpAffine(image, img_t, rotation_matrix, image.size());

	// calculating size of window to show two image
	cv::Mat matWindow(cv::Size(image.cols * 2, image.rows), image.type(), cv::Scalar::all(0));

	// copy input image to window matrix
	img_tmp = matWindow(cv::Rect(0, 0, image.cols, image.rows));
	image.copyTo(img_tmp);

	// copy transformed image to window matrix
	img_tmp = matWindow(cv::Rect(image.cols, 0, image.cols, image.rows));
	img_t.copyTo(img_tmp);

	// reshow original and transformed image
	cv::imshow("Original and Transformed image", matWindow);
}

int main(int argc, char** argv) {

	// read the image and display it
	// cv::IMREAD_UNCHANGED - image is read “as is”, color or grayscale
	image = cv::imread("../../img/book_perspective.png", cv::IMREAD_UNCHANGED);

	// always check if the image was successfully read!!!
	if (image.empty()) return -1;

	// calculating size of window to show two image
	cv::Mat matWindow(cv::Size(image.cols * 2, image.rows), image.type(), cv::Scalar::all(0));

	// copy input image to window matrix
	img_tmp = matWindow(cv::Rect(0, 0, image.cols, image.rows));
	image.copyTo(img_tmp);

	// generate matrix rotation with arbitrary angle and center of rotation (cv::getRotationMatrix2D)
	cv::Mat rotation_matrix = cv::getRotationMatrix2D(cv::Point2f(cy_slider, cx_slider), angle_slider, 1);
	// implamate rotate matrix on transformed image (cv::warpAffine)
	cv::warpAffine(image, img_t, rotation_matrix, image.size());

	// copy transformed image to window matrix
	img_tmp = matWindow(cv::Rect(image.cols, 0, image.cols, image.rows));
	img_t.copyTo(img_tmp);

	// show original and transformed image
	cv::imshow("Original and Transformed image", matWindow);

	// create trackbar for selected angle
	cv::createTrackbar("Angle ", "Original and Transformed image", &angle_slider, 360, on_trackbar);

	// create trackbar for selected center of rotation
	cv::createTrackbar("X coordinate", "Original and Transformed image", &cx_slider, image.cols / 2, on_trackbar);
	cv::createTrackbar("Y coordinate", "Original and Transformed image", &cy_slider, image.rows / 2, on_trackbar);

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
