#include "opencv2/opencv.hpp"

using namespace cv;

#define COLOROP1 0
#define COLOROP2 0
#define SPLIT 0
#define COLORHIST 0
#define INRANGE 0
#define BACKPRO 1

int lower_hue = 40, upper_hue = 80;
Mat src, src_hsv, mask;
void on_hue_changed(int pos, void* userdata) {
	Scalar lowerb(lower_hue, 100, 0);
	Scalar upperb(upper_hue, 255, 255);
	inRange(src_hsv, lowerb, upperb, mask);
	imshow("mask", mask);
}
void color_reverse() {
	Mat src = imread("../src/butterfly.jpg", IMREAD_COLOR);

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);
			Vec3b& p2 = dst.at<Vec3b>(j, i);

			// same as "Mat dst = Scalar(255, 255, 255) - src
			p2[0] = 255 - p1[0];
			p2[1] = 255 - p1[1];
			p2[2] = 255 - p1[2];
		}
	}
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}
void color_grayscale() {
	Mat src = imread("../src/butterfly.jpg", IMREAD_COLOR);
	Mat dst1, dst2;
	cvtColor(src, dst1, COLOR_BGR2GRAY);
	cvtColor(dst1, dst2, COLOR_GRAY2BGR);
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();
	destroyAllWindows();
}
void color_split() {
	Mat src = imread("../src/candies.png");
	std::vector<Mat> bgr_planes;
	split(src, bgr_planes);
	imshow("src", src);
	imshow("B_Plane", bgr_planes[0]);
	imshow("G_Plane", bgr_planes[1]);
	imshow("R_Plane", bgr_planes[2]);
	waitKey();
	destroyAllWindows();
}
void color_histogram() {
	Mat src = imread("../src/pepper.bmp");
	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);
	std::vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes);
	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]);
	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb);
	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}
void color_inRange() {
	src = imread("../src/candies.png");
	cvtColor(src, src_hsv, COLOR_BGR2HSV);
	imshow("src", src);
	namedWindow("mask");
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
	on_hue_changed(0, 0);
	waitKey();
	destroyAllWindows();
}
void color_backpro() {
	Mat ref, ref_ycrcb, mask;
	ref = imread("../src/ref.png", IMREAD_COLOR);
	mask = imread("../src/mask.bmp", IMREAD_GRAYSCALE);
	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

	Mat hist;
	int channels[] = { 1,2 };
	int cr_bins = 128; int cb_bins = 128;
	int histSize[] = { cr_bins, cb_bins };
	float cr_range[] = { 0,256 };
	float cb_range[] = { 0,256 };
	const float* ranges[] = { cr_range, cb_range };

	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

	Mat src, src_ycrcb;
	src = imread("../src/kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	Mat backproj;
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);
	hist.convertTo(hist, CV_8UC1);
	imshow("src", src);
	imshow("backproj", backproj);
	imshow("hist", hist);
	waitKey();
	destroyAllWindows();
}

int main(void) {
#if COLOROP1 == 1
	color_reverse();
#endif
#if COLOROP2 == 1
	color_grayscale();
#endif
#if SPLIT == 1
	color_split();
#endif
#if COLORHIST == 1
	color_histogram();
#endif
#if INRANGE == 1
	color_inRange();
#endif
#if BACKPRO == 1
	color_backpro();
#endif
}