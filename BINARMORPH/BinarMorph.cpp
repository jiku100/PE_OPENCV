#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

#define THRESHOLD 0
#define ADAPTIVE 0
#define ERODEDILATE 0
#define OPENCLOSE 1

void on_threshold(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;
	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY);
	imshow("dst", dst);
}
void threshold() {
	Mat src = imread("../src/neutrophils.png", IMREAD_GRAYSCALE);
	imshow("src", src);
	namedWindow("dst");
	createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void*)&src);
	setTrackbarPos("Threshold", "dst", 128);
	waitKey();
	destroyAllWindows();
}

int bsize;
int c;
void on_trackbar_size(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;
	bsize = pos;
	if (bsize % 2 == 0) bsize--;
	if (bsize < 3) bsize = 3;

	Mat dst;
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, bsize, c);
	imshow("dst", dst);
}
void on_trackbar_c(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;
	c = pos;
	Mat dst;
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, bsize, c);
	imshow("dst", dst);
}
void adaptive() {
	Mat src = imread("../src/sudoku.jpg", IMREAD_GRAYSCALE);
	imshow("src", src);
	namedWindow("dst");
	createTrackbar("Block Size", "dst", 0, 200, on_trackbar_size, (void*)&src);
	setTrackbarPos("Block Size", "dst", 11);
	createTrackbar("C", "dst", 0, 200, on_trackbar_c, (void*)&src);
	setTrackbarPos("C", "dst", 5);
	waitKey();
	destroyAllWindows();
}

void erode_dilate() {
	Mat src = imread("../src/milkdrop.bmp", IMREAD_GRAYSCALE);
	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat dst1, dst2;
	erode(bin, dst1, Mat());
	dilate(bin, dst2, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("erode", dst1);
	imshow("dilate", dst2);
	waitKey();
	destroyAllWindows();
}

void open_close() {
	Mat src = imread("../src/milkdrop.bmp", IMREAD_GRAYSCALE);
	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat dst1, dst2, dst3;
	morphologyEx(bin, dst1, MORPH_OPEN, Mat());
	morphologyEx(bin, dst2, MORPH_CLOSE, Mat());
	morphologyEx(bin, dst3, MORPH_GRADIENT, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("open", dst1);
	imshow("close", dst2);
	imshow("gradient", dst3);
	waitKey();
	destroyAllWindows();
}
int main(void) {
#if THRESHOLD == 1
	threshold();
#endif
#if ADAPTIVE == 1
	adaptive();
#endif
#if ERODEDILATE == 1
	erode_dilate();
#endif
#if OPENCLOSE == 1
	open_close();
#endif
}