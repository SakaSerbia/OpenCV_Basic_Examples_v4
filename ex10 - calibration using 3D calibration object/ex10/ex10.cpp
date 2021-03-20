// ex10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Point2f uvPoints[18];
Point3f XYZPoints[18];

int nr_points = 18;

// A matrix in SVD algorithm
Mat A = Mat::zeros(nr_points * 2, 12, CV_32F);
// read image
Mat src;
// read image with circle
Mat image_w_circle;

// position on 3D box
int X = 0, Y = 0, Z = 0;

Mat test_point_XYZ(4, 1, CV_32F);
Mat test_point_uv(3, 1, CV_32F);
Mat CameraMatrix(3, 4, CV_32F);

static void on_trackbar(int, void*)
{
	test_point_XYZ.at<float>(0, 0) = X; // X
	test_point_XYZ.at<float>(1, 0) = Y; // Y
	test_point_XYZ.at<float>(2, 0) = Z; // Z
	test_point_XYZ.at<float>(3, 0) = 1; // homogenisation

	test_point_uv = CameraMatrix * test_point_XYZ;

	float u = test_point_uv.at<float>(0, 0) / test_point_uv.at<float>(2, 0);
	float v = test_point_uv.at<float>(1, 0) / test_point_uv.at<float>(2, 0);

	// Copy read image for new matrix
	src.copyTo(image_w_circle);
	// drow circle on image
	circle(image_w_circle, Point(u, v), 10, Scalar(0, 0, 255), 3);
	// show image with circle/points
	imshow("Image width point", image_w_circle);
}

int main(void) {

	// read the image
	src = imread("../../img/cube_org.png");

	// always check if the image was successfully read!!!
	if (src.empty()) return -1;

	uvPoints[0] = Point2f(535, 253);
	uvPoints[1] = Point2f(640, 239);
	uvPoints[2] = Point2f(763, 222);
	uvPoints[3] = Point2f(886, 221);
	uvPoints[4] = Point2f(985, 234);
	uvPoints[5] = Point2f(1067, 246);

	uvPoints[6] = Point2f(535, 398);
	uvPoints[7] = Point2f(641, 397);
	uvPoints[8] = Point2f(765, 394);
	uvPoints[9] = Point2f(890, 392);
	uvPoints[10] = Point2f(985, 393);
	uvPoints[11] = Point2f(1070, 392);

	uvPoints[12] = Point2f(535, 545);
	uvPoints[13] = Point2f(641, 554);
	uvPoints[14] = Point2f(765, 566);
	uvPoints[15] = Point2f(890, 536);
	uvPoints[16] = Point2f(987, 550);
	uvPoints[17] = Point2f(1070, 538);

	XYZPoints[0] = Point3f(0, 5, 5);
	XYZPoints[1] = Point3f(0, 3, 5);
	XYZPoints[2] = Point3f(0, 1, 5);
	XYZPoints[3] = Point3f(1, 0, 5);
	XYZPoints[4] = Point3f(3, 0, 5);
	XYZPoints[5] = Point3f(5, 0, 5);

	XYZPoints[6] = Point3f(0, 5, 3);
	XYZPoints[7] = Point3f(0, 3, 3);
	XYZPoints[8] = Point3f(0, 1, 3);
	XYZPoints[9] = Point3f(1, 0, 3);
	XYZPoints[10] = Point3f(3, 0, 3);
	XYZPoints[11] = Point3f(5, 0, 3);

	XYZPoints[12] = Point3f(0, 5, 1);
	XYZPoints[13] = Point3f(0, 3, 1);
	XYZPoints[14] = Point3f(0, 1, 1);
	XYZPoints[15] = Point3f(1, 0, 1);
	XYZPoints[16] = Point3f(3, 0, 1);
	XYZPoints[17] = Point3f(5, 0, 1);


	for (int i = 0; i < nr_points; i++) {
		A.at<float>(2 * i, 0) = -XYZPoints[i].x;
		A.at<float>(2 * i, 1) = -XYZPoints[i].y;
		A.at<float>(2 * i, 2) = -XYZPoints[i].z;
		A.at<float>(2 * i, 3) = -1;
		A.at<float>(2 * i, 4) = 0;
		A.at<float>(2 * i, 5) = 0;
		A.at<float>(2 * i, 6) = 0;
		A.at<float>(2 * i, 7) = 0;
		A.at<float>(2 * i, 8) = XYZPoints[i].x * uvPoints[i].x;
		A.at<float>(2 * i, 9) = XYZPoints[i].y * uvPoints[i].x;
		A.at<float>(2 * i, 10) = XYZPoints[i].z * uvPoints[i].x;
		A.at<float>(2 * i, 11) = uvPoints[i].x;

		A.at<float>(2 * i + 1, 0) = 0;
		A.at<float>(2 * i + 1, 1) = 0;
		A.at<float>(2 * i + 1, 2) = 0;
		A.at<float>(2 * i + 1, 3) = 0;
		A.at<float>(2 * i + 1, 4) = -XYZPoints[i].x;
		A.at<float>(2 * i + 1, 5) = -XYZPoints[i].y;
		A.at<float>(2 * i + 1, 6) = -XYZPoints[i].z;
		A.at<float>(2 * i + 1, 7) = -1;
		A.at<float>(2 * i + 1, 8) = XYZPoints[i].x * uvPoints[i].y;
		A.at<float>(2 * i + 1, 9) = XYZPoints[i].y * uvPoints[i].y;
		A.at<float>(2 * i + 1, 10) = XYZPoints[i].z * uvPoints[i].y;
		A.at<float>(2 * i + 1, 11) = uvPoints[i].y;
	}

	// SVD algorithm
	// the solution that gives the smallest error corresponds to the column
	// in the matrix Vt whitch corresponds to the smallest eigenvalue in 
	// the diagonal matrix W
	Mat w, u, vt;
	SVD::compute(A, w, u, vt);
	float smallestSv = w.at<float>(0, 0);
	unsigned int indexSmallestSv = 0;

	for (int i = 1; i < w.rows; i++) {
		if ((w.at<float>(i, 0) < smallestSv)) {
			smallestSv = w.at<float>(i, 0);
			indexSmallestSv = i;
		}
	}

	// parameter vector
	cv::Mat h = vt.row(indexSmallestSv);

	// tz < 0
	if (h.at<float>(0, 11) < 0) {
		h *= -1;
	}

	// forming a matrix from the parameter vector
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			CameraMatrix.at<float>(i, j) = h.at<float>(0, 4 * i + j);
		}
	}

	// print matrix elements 
	cout << "CameraMatrix = " << endl << " " << CameraMatrix << endl << endl;

	// show the image and track bars
	imshow("Image width point", src);
	createTrackbar("X", "Image width point", &X, 5, on_trackbar);
	createTrackbar("Y", "Image width point", &Y, 5, on_trackbar);
	createTrackbar("Z", "Image width point", &Z, 5, on_trackbar);
	on_trackbar(X, 0);

	// to keep the window open we use waitKey(msdelay), 0 is forever
	waitKey();

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
