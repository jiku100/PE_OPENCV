#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

#define ARITHMETIC 0
#define LOGICAL 1
void arithmetic() {
	Mat src1 = imread("../src/lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("../src/square.bmp", IMREAD_GRAYSCALE);

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	add(src1, src2, dst1);
	addWeighted(src1, 0.5, src2, 0.5, 0, dst2);
	subtract(src1, src2, dst3);
	absdiff(src1, src2, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey();
	destroyAllWindows();
}
void logical() {
	Mat src1 = imread("../src/lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("../src/square.bmp", IMREAD_GRAYSCALE);

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	bitwise_and(src1, src2, dst1);	// dst1 = src1 & src2
	bitwise_or(src1, src2, dst2);	// dst2 = src1 | src2
	bitwise_xor(src1, src2, dst3);	// dst3 = src1 ^ src2
	bitwise_not(src1, dst4);		// dst4 = ~src1

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey();
	destroyAllWindows();
}

int main(void) {
#if ARITHMETIC == 1
	arithmetic();
#endif
#if LOGICAL == 1
	logical();
#endif
}