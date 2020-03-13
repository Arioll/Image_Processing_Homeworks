#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

Mat GetBrightnessImg(Mat image, uint color_ind) {
	vector<Mat> channels;
	split(image, channels);
	vector<Mat> to_merge;
	for (int i = 0; i < 3; i++) {
		to_merge.push_back(channels[color_ind]);
	}
	Mat one_color_image = Mat::zeros(image.size[0], image.size[1], CV_8UC3);
	merge(to_merge, one_color_image);
	return one_color_image;
}

Mat GetOneColorImg(Mat image, uint color_ind) {
	vector<Mat> channels;
	split(image, channels);
	Mat mask = Mat::zeros(image.size[0], image.size[1], CV_8UC1);
	vector<Mat> to_merge;
	for (int i = 0; i < 3; i++) {
		if (i == color_ind) {
			to_merge.push_back(channels[color_ind]);
		}
		else {
			to_merge.push_back(mask);
		}
	}
	Mat one_color_image = Mat::zeros(image.size[0], image.size[1], CV_8UC3);
	merge(to_merge, one_color_image);
	return one_color_image;
}

void Lab2() {
	Mat display = Mat::zeros(256 * 2, 256 * 4, CV_8UC3);
	Mat image = imread("image.png", IMREAD_COLOR);
	cout << image.size << endl;
	auto rect = Rect(0, 0, image.size[0], image.size[1]);
	auto roi = display(rect);
	image.copyTo(roi);

	for (int i = 1; i <= 3; i++) {
		auto rect = Rect(256 * i, 0, image.size[0], image.size[1]);
		auto roi = display(rect);
		Mat img = GetBrightnessImg(image, i - 1);
		img.copyTo(roi);
	}

	for (int i = 1; i <= 3; i++) {
		auto rect = Rect(256 * i, 256, image.size[0], image.size[1]);
		auto roi = display(rect);
		Mat img = GetOneColorImg(image, i - 1);
		img.copyTo(roi);
	}

	imshow("image", display);
	waitKey(0);
}

int main() {
	Lab2();
}