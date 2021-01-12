#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define BRIGHTNESS1 0
#define BRIGHTNESS2 0
#define BRIGHTNESS3 0
#define CONTRAST1 0
#define CONTRAST2 1

void brightness1() {
	// 연산자와 함수를 통해 밝기 조절
	Mat src = imread("../src/lenna.bmp", IMREAD_GRAYSCALE);
	Mat up = src + 100;
	Mat down;
	subtract(src, 100, down);
	imshow("src", src);
	imshow("up", up);
	imshow("down", down);
	waitKey();
	destroyAllWindows();
	return;
}
void brightness2() {
	// 직접 픽셀에 접근하여 밝기 조절
	Mat src = imread("../src/lenna.bmp", IMREAD_GRAYSCALE);
	Mat dst(src.rows, src.cols, src.type());
	// 직접 픽셀로 접근할 때는 overflow 발생
	for (int j = 0; j < src.rows; j++) {
		uchar* srcPtr = src.ptr<uchar>(j);
		uchar* dstPtr = dst.ptr<uchar>(j);
		for (int i = 0; i < src.cols; i++) {
			dstPtr[i] = srcPtr[i] + 100;
		}
	}
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
	// 따라서 saturation 직접 구현
	for (int j = 0; j < src.rows; j++) {
		uchar* dstPtr = dst.ptr<uchar>(j);
		for (int i = 0; i < src.cols; i++) {
			dstPtr[i] = dstPtr[i] > 255 ? 255 : dstPtr[i] < 0 ? 0 : dstPtr[i];
		}
	}
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
	// OpenCV에 자체 함수도 존재
	for (int j = 0; j < src.rows; j++) {
		uchar* dstPtr = dst.ptr<uchar>(j);
		for (int i = 0; i < src.cols; i++) {
			dstPtr[i] = saturate_cast<uchar>(dstPtr[i]);
		}
	}
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
	return;
}
void on_brightness(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;
	imshow("dst", dst);
}
void brightness3() {
	Mat src = imread("../src/lenna.bmp", IMREAD_GRAYSCALE);
	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src);
	on_brightness(0, (void*)&src);
	imshow("src", src);
	waitKey();
	destroyAllWindows();
	return;
}
void contrast1() {
	Mat src = imread("../src/lenna.bmp", IMREAD_GRAYSCALE);
	float s = 2.f;
	Mat dst = s * src;
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
	return;
}
void contrast2() {
	Mat src = imread("../src/lenna.bmp", IMREAD_GRAYSCALE);
	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
	return;
}
int main(void) {
#if BRIGHTNESS1 == 1
	brightness1();
#endif
#if BRIGHTNESS2 == 1
	brightness2();
#endif
#if BRIGHTNESS3 == 1
	brightness3();
#endif
#if CONTRAST1 == 1
	contrast1();
#endif
#if CONTRAST2 == 1
	contrast2();
#endif
	return 0;
}