#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

#define TRANSFORM 0
#define TRANSLATE 0
#define SHEAR 0
#define SCALE 0
#define ROTATE 0
#define FLIP 0
#define PERSPECTIVE 1

Mat src;
Point2f srcQuad[4], dstQuad[4];
void affine_transform() {
	Mat src = imread("../src/tekapo.bmp");
	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);
	srcPts[1] = Point2f(src.cols - 1, 0);
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
	dstPts[0] = Point2f(50, 50);
	dstPts[1] = Point2f(src.cols - 100, 100);
	dstPts[2] = Point2f(src.cols - 50, src.rows - 50);

	Mat m = getAffineTransform(srcPts, dstPts);
	std::cout << m << std::endl;
	Mat dst1;
	Mat dst2;
	warpAffine(src, dst1, m, Size());
	warpAffine(src, dst2, m, Size(), INTER_LINEAR | WARP_INVERSE_MAP);
	
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
	return;
}
void affine_translate() {
	Mat src = imread("../src/tekapo.bmp");
	Mat m = Mat_<double>({ 2,3 }, { 1, 0, 150, 0, 1, 100 });
	Mat dst;
	warpAffine(src, dst, m, Size());
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
	return;
}
void affine_shear() {
	Mat src = imread("../src/tekapo.bmp");
	double mx = 0.3;
	Mat M = Mat_<double>({ 2,3 }, { 1,mx,0,0,1,0 });

	Mat dst;
	warpAffine(src, dst, M, Size(cvRound(src.cols + src.rows * mx), src.rows));
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
	return;
}
void affine_scale() {
	Mat src = imread("../src/rose.bmp");
	
	Mat dst1, dst2, dst3, dst4;
	resize(src, dst1, Size(), 4, 4, INTER_NEAREST);
	resize(src, dst2, Size(1920, 1280));
	resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);
	resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);

	Mat dsts[] = { dst1, dst2, dst3, dst4 };
	imshow("src", src);
	for (int i = 1; i < 5; i++) {
		String title = format("dst%d", i);
		imshow(title, dsts[i - 1](Rect(400, 500, 400, 400)));
	}
	waitKey();
	destroyAllWindows();
	return;
}
void affine_rotation() {
	Mat src = imread("../src/tekapo.bmp");
	Point2f cp(src.cols / 2.f, src.rows / 2.f);
	Mat m = getRotationMatrix2D(cp, 20, 1);
	Mat dst;
	warpAffine(src, dst, m, Size());
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
	return;
}
void affine_flip() {
	Mat src = imread("../src/eastsea.bmp");
	imshow("src", src);

	Mat dst;
	int flipCode[] = { -1, 0, 1 };
	for (int i = 0; i < 3; i++) {
		flip(src, dst, flipCode[i]);
		String desc = format("flipCode: %d", flipCode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 1, LINE_AA);
		String title = format("dst%d", i + 1);
		imshow(title, dst);
	}
	waitKey();
	destroyAllWindows();
	return;
}
void on_mouse(int event, int x, int y, int flags, void* userdata) {
	static int cnt = 0;
	if (event == EVENT_LBUTTONDOWN) {
		if (cnt < 4) {
			srcQuad[cnt++] = Point2f(x, y);
			circle(src, Point(x, y), 5, Scalar(0, 0, 255), -1);
			imshow("src", src);
			if (cnt == 4) {
				int w = 200, h = 300;
				dstQuad[0] = Point2f(0, 0);
				dstQuad[1] = Point2f(w - 1, 0);
				dstQuad[2] = Point2f(w - 1, h - 1);
				dstQuad[3] = Point2f(0, h - 1);
				Mat pers = getPerspectiveTransform(srcQuad, dstQuad);
				Mat dst;
				warpPerspective(src, dst, pers, Size(w, h));
				imshow("dst", dst);
			}
		}
	}	
}
void perspective() {
	src = imread("../src/card.bmp");
	namedWindow("src");
	setMouseCallback("src", on_mouse);
	imshow("src", src);
	waitKey();
	destroyAllWindows();
	return;
}

int main(void) {
#if TRANSFORM == 1
	affine_transform();
#endif
#if TRANSLATE == 1
	affine_translate();
#endif
#if SHEAR == 1
	affine_shear();
#endif
#if SCALE == 1
	affine_scale();
#endif
#if ROTATE == 1
	affine_rotation();
#endif
#if FLIP == 1
	affine_flip();
#endif
#if PERSPECTIVE == 1
	perspective();
#endif
}