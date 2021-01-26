#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

#define LABEL1 0
#define LABEL2 0
#define CONTOUR1 0
#define CONTOUR2 0
#define BOUNDING 1

void labeling_basic() {
	uchar data[] = {
		0,0,1,1,0,0,0,0,
		1,1,1,1,0,0,1,0,
		1,1,1,1,0,0,0,0,
		0,0,0,0,0,1,1,0,
		0,0,0,1,1,1,1,0,
		0,0,0,1,0,0,1,0,
		0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,
	};
	Mat src = Mat(8, 8, CV_8UC1, data) * 255;
	Mat labels;
	int cnt = connectedComponents(src, labels);
	std::cout << "src:\n" << src << std::endl;
	std::cout << "labels:\n" << labels << std::endl;
	std::cout << "number of labels: " << cnt << std::endl;
}
void labeling_stats() {
	Mat src = imread("../src/keyboard.bmp", IMREAD_GRAYSCALE);
	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);
	
	for (int i = 0; i < cnt; i++) {
		int* p = stats.ptr<int>(i);
		if (p[4] < 20) continue;
		rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255), 2);
	}
	std::cout << "stats:\n" << stats << std::endl;
	imshow("src", src);
	imshow("bin", bin);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}
void contours_basic() {
	Mat src = imread("../src/contours.bmp", IMREAD_GRAYSCALE);
	std::vector<std::vector<Point>> contours;
	findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (int i = 0; i < contours.size(); i++) {
		Scalar c(rand() & 255, rand() % 255, rand() & 255);
		drawContours(dst, contours, i, c, 2);
	}
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}
void contours_hier() {
	Mat src = imread("../src/contours.bmp", IMREAD_GRAYSCALE);
	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hier;
	findContours(src, contours, hier, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (int idx = 0; idx >= 0; idx = hier[idx][0]) {
		Scalar c(rand() & 255, rand() % 255, rand() & 255);
		drawContours(dst, contours, idx, c, -1, LINE_8, hier);
	}
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}
void setLabel(Mat& img, const std::vector<Point>& pts, const String& label) {
	Rect rc = boundingRect(pts);
	rectangle(img, rc, Scalar(0, 0, 255), 1);
	putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
}
void bounding() {
	Mat img = imread("../src/polygon.bmp", IMREAD_COLOR);
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Mat bin;
	threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);
	std::vector<std::vector<Point>> contours;
	findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	for (std::vector<Point>& pts : contours) {
		if (contourArea(pts) < 400)
			continue;
		std::cout << "근사 전 점의 개수: " << (int)pts.size() << std::endl;
		std::vector<Point> approx;
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);
		int vtc = (int)approx.size();
		std::cout << "근사 후 점의 개수: " << vtc << std::endl << std::endl;

		std::vector<std::vector<Point>> approx_contours;
		approx_contours.push_back(approx);
		drawContours(img, approx_contours, -1, Scalar(0, 255, 255), 2);

		if (vtc == 3) {
			setLabel(img, pts, "TRI");
		}
		else if (vtc == 4) {
			setLabel(img, pts, "RECT");
		}
		else {
			double len = arcLength(pts, true);
			double area = contourArea(pts);
			double ratio = 4. * CV_PI * area / (len * len);
			if (ratio > 0.8) {
				setLabel(img, pts, "CIR");
			}
		}
	}
	imshow("img", img);
	waitKey();
	destroyAllWindows();
}
int main(void) {
#if LABEL1 == 1
	labeling_basic();
#endif
#if LABEL2 == 1
	labeling_stats();
#endif
#if CONTOUR1 == 1
	contours_basic();
#endif
#if CONTOUR2 == 1
	contours_hier();
#endif
#if BOUNDING == 1
	bounding();
#endif
}