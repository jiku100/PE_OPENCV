#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define MASKSETTO 0
#define MASKCOPYTO 0
#define TICKMETER 0
#define SUMMEAN 0
#define MINMAX 0
#define NORMALIZE 0
#define CVROUND 1

void mask_setTo() {
	Mat src = imread("../src/lenna.bmp", IMREAD_COLOR);
	Mat mask = imread("../src/mask_smile.bmp", IMREAD_GRAYSCALE);

	src.setTo(Scalar(0, 255, 255), mask);	// mask 에서 value가 0이 아닌 곳만 src 색깔 노란색으로 설정
	imshow("src", src);
	imshow("mask", mask);

	waitKey();
	destroyAllWindows();
	return;
}
void mask_copyTo() {
	Mat src = imread("../src/airplane.bmp", IMREAD_COLOR);
	Mat mask = imread("../src/mask_plane.bmp", IMREAD_GRAYSCALE);
	Mat dst = imread("../src/field.bmp", IMREAD_COLOR);

	src.copyTo(dst, mask);	// src에서 mask에 해당되는 부분만 dst에 복사. 나머지는 유지

	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
	return;
}
void time_inverse() {
	Mat src = imread("../src/lenna.bmp", IMREAD_COLOR);
	Mat dst(src.rows, src.cols, src.type());

	TickMeter tm;	// TickMeter 생성
	tm.start();	// 시간 측정 시작

	for (int j = 0; j < src.rows; j++)
		for (int i = 0; i < src.cols; i++)
			dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i);

	tm.stop();	//시간 측정 끝

	cout << "Image inverse took " << tm.getTimeMilli() << "ms." << endl;	// 밀리초 단위로 반환
	return;
}
void sum_mean() {
	Mat src = imread("../src/lenna.bmp", IMREAD_COLOR);
	
	cout << "Sum: " << sum(src)<< endl;
	cout << "Mean: " << mean(src) << endl;
	return;
}
void minMax() {
	Mat src = imread("../src/lenna.bmp", IMREAD_GRAYSCALE);
	double minVal, maxVal;
	Point minPos, maxPos;
	minMaxLoc(src, &minVal, &maxVal, &minPos, &maxPos);

	cout << "minVal: " << minVal << " at " << minPos << endl;
	cout << "maxVal: " << maxVal << " at " << maxPos << endl;
	return;
}
void normal() {
	Mat src = Mat_<float>({ 1,5 }, { -1.f, -0.5f, 0.f, 0.5f, 1.f });
	Mat dst;
	normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);	// 0 ~ 255로 정규화
	cout << "src: " << src << endl;
	cout << "dst: " << dst << endl;
	return;
}
void round() {
	cout << "cvRound(2.5): " << cvRound(2.5) << endl;
	cout << "cvRound(2.51): " << cvRound(2.51) << endl;
	cout << "cvRound(3.4999): " << cvRound(3.4999) << endl;
	cout << "cvRound(3.5): " << cvRound(3.5) << endl;
}
int main(void) {
#if MASKSETTO == 1
	mask_setTo();
#endif
#if MASKCOPYTO == 1
	mask_copyTo();
#endif
#if TICKMETER == 1
	time_inverse();
#endif
#if SUMMEAN == 1
	sum_mean();
#endif
#if MINMAX == 1
	minMax();
#endif
#if NORMALIZE == 1
	normal();
#endif
#if CVROUND == 1
	round();
#endif
}
