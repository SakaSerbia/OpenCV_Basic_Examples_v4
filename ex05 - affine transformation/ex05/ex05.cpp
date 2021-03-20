// ex05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// include file for every supported OpenCV function
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {

	// notice here that we are using the Opencv's embedded "String" class
	//std::vector<cv::String> filenames;

	// again we are using the Opencv's embedded "String" class
	//cv::String folder = "../../img";

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

	// infinite loop
	for (int frame = 0;; ++frame) {

		// center of the image
		cv::Point2f center(inImage.cols * 0.5f, inImage.rows * 0.5f);

		// calculating angle
		double angle = frame * 3 % 360;

		// calculating scale
		double scale = (cos((angle - 60) * CV_PI / 180) + 1.05) * 0.8;

		cv::Mat rot_mat = cv::getRotationMatrix2D(
			center,    // center of rotation
			angle,     // angle of rotation
			scale      // rescale after rotation
		);             // return 2-by-3 matrix

		cv::warpAffine(
			inImage,              // input image
			transImage,           // result image
			rot_mat,              // 2-by-3 transform mtx
			inImage.size(),       // destination image size
			cv::INTER_LINEAR,     // interpolation, inverse
			cv::BORDER_CONSTANT,  // pixel extrapolation
			cv::Scalar()          // for constant borders
		);

		// show transformed image
		//cv::imshow("Rotated image", transImage);

		// copy transformed image to window matrix
		matRoi = matWindow(cv::Rect(inImage.cols, 0, inImage.cols, inImage.rows));
		transImage.copyTo(matRoi);

		cv::imshow("Original and transformed image", matWindow);

		if (cv::waitKey(30) >= 0)
			break;
	}

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
