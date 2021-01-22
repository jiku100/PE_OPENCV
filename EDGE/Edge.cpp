#include "opencv2/opencv.hpp"

using namespace cv;

#define SOBEL 0
#define CANNY 0
#define LINE 0
#define LINEP 0
#define CIRCLE 1

void sobel_edge() {
	Mat src = imread("../src/lenna.bmp", IMREAD_GRAYSCALE);
	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat fmag, mag;
	magnitude(dx, dy, fmag);
	fmag.convertTo(mag, CV_8UC1);

	Mat edge = mag > 120;

	dx.convertTo(dx, CV_8UC1);
	dy.convertTo(dy, CV_8UC1);
	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);
	imshow("dx", dx);
	imshow("dy", dy);
	waitKey();
	destroyAllWindows();
}
void canny_edge() {
	Mat src = imread("../src/lenna.bmp", IMREAD_GRAYSCALE);
	Mat dst1, dst2;
	Canny(src, dst1, 50, 100);
	Canny(src, dst2, 50, 150);
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();
	destroyAllWindows();
}
void hough_line() {
	Mat src = imread("../src/building.jpg", IMREAD_GRAYSCALE);
	Mat edge;
	Canny(src, edge, 50, 150);
	std::vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250);
	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);
	for (size_t i = 0; i < lines.size(); i++) {
		float r = lines[i][0], t = lines[i][1];
		double cos_t = cos(t), sin_t = sin(t);
		double x0 = r * cos_t, y0 = r * sin_t;
		double alpha = 1000;

		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
	}
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}
void hough_line_segments() {
	Mat src = imread("../src/building.jpg", IMREAD_GRAYSCALE);
	Mat edge;
	Canny(src, edge, 50, 150);
	std::vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);
	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);
	for (Vec4i l : lines) {
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}
void hough_circle() {
	Mat src = imread("../src/coins.png", IMREAD_GRAYSCALE);
	Mat blurred;
	blur(src, blurred, Size(3, 3));
	std::vector<Vec3f> circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);
	for (Vec3f c : circles) {
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

int main(void) {
#if SOBEL == 1
	sobel_edge();
#endif
#if CANNY == 1
	canny_edge();
#endif
#if LINE == 1
	hough_line();
#endif
#if LINEP == 1
	hough_line_segments();
#endif
#if CIRCLE == 1
	hough_circle();
#endif
}