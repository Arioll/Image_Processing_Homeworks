#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void Lab1() {
	Mat A = Mat::zeros(180, 768, CV_8UC1);
	double alpha, beta;
	alpha = 0.9;
	beta = 0.1;
	for (int i = 0; i < 256; i++) {
		auto rect = Rect(i * 3, 0, 3, 60);
		auto image_roi = A(rect);
		image_roi.setTo(i);

		auto rect1 = Rect(i * 3, 60, 3, 60);
		auto image_roi1 = A(rect1);
		image_roi1.setTo(alpha * i + beta);
	}
	for (int i = 0; i < 768 / 30; i++) {
		auto rect1 = Rect(i * 30, 120, 30, 60);
		auto image_roi1 = A(rect1);
		image_roi1.setTo(255 * (i * 30) / 768);
	}
	auto rect1 = Rect(int(768 / 30) * 30, 120, (768 % 30), 60);
	auto image_roi1 = A(rect1);
	image_roi1.setTo(255);
	
	imshow("x", A);
	waitKey(0);
}

//int main() {
//	Lab1();
//}