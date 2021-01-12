#include "opencv2/opencv.hpp"

using namespace cv;

#define HISTOGRAM1 0
#define HISTOGRAM2 0
#define STRETCHING 0
#define EQUALIZE 1
Mat calcGrayHist(const Mat& img) {
	CV_Assert(img.type() == CV_8UC1);
	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0,256 };
	const float* ranges[] = { graylevel };
	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);
	return hist;
}
Mat getGrayHistImage(const Mat& hist) {
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));
	double histMax;
	minMaxLoc(hist, 0, &histMax);
	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100), Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}
	return imgHist;
}
void histogram1() {
	Mat src = imread("../src/hawkes.bmp", IMREAD_GRAYSCALE);
	Mat hist = calcGrayHist(src);
	Mat hist_img = getGrayHistImage(hist);
	imshow("src", src);
	imshow("srcHist", hist_img);
	waitKey();
	destroyAllWindows();
	return;
}
void histogram2() {
	Mat src = imread("../src/lenna.bmp", IMREAD_GRAYSCALE);
	Mat src_hist = getGrayHistImage(calcGrayHist(src));
	Mat up = src + 30;
	Mat up_hist = getGrayHistImage(calcGrayHist(up));
	Mat down = src - 30;
	Mat down_hist = getGrayHistImage(calcGrayHist(down));
	Mat high = src + (src - 128) * 0.5f;
	Mat high_hist = getGrayHistImage(calcGrayHist(high));
	Mat low = src + (src - 128) * -0.5f;
	Mat low_hist = getGrayHistImage(calcGrayHist(low));
	imshow("src", src);
	imshow("src_hist", src_hist);
	imshow("up", up);
	imshow("up_hist", up_hist);
	imshow("down", down);
	imshow("down_hist", down_hist);
	imshow("high", high);
	imshow("high_hist", high_hist);
	imshow("low", low);
	imshow("low_hist", low_hist);
	waitKey();
	destroyAllWindows();
	return;
}
void stretching() {
	Mat src = imread("../src/hawkes.bmp", IMREAD_GRAYSCALE);
	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);
	Mat dst = (src - gmin) * 255 / (gmax - gmin);
	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));
	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));
	waitKey();
	destroyAllWindows();
	return;
}
void equalization() {
	Mat src = imread("../src/hawkes.bmp", IMREAD_GRAYSCALE);
	Mat dst;
	equalizeHist(src, dst);
	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));
	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));
	waitKey();
	destroyAllWindows();
	return;
}
int main(void) {
#if HISTOGRAM1 == 1
	histogram1();
#endif
#if HISTOGRAM2 == 1
	histogram2();
#endif
#if STRETCHING == 1
	stretching();
#endif
#if EQUALIZE == 1
	equalization();
#endif
}