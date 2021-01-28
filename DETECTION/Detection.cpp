#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

#define TEMPLATE 0
#define FACE 0
#define EYE 0
#define HOG 0
#define QR 1

void template_matching() {
	Mat img = imread("../src/circuit.bmp", IMREAD_COLOR);
	Mat templ = imread("../src/crystal.bmp", IMREAD_COLOR);

	img = img + Scalar(50, 50, 50);

	Mat noise(img.size(), CV_32SC3);
	randn(noise, 0, 10);
	add(img, noise, img, Mat(), CV_8UC3);
	
	Mat res, res_norm;
	matchTemplate(img, templ, res, TM_CCOEFF_NORMED);
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);

	double maxv;
	Point maxloc;
	minMaxLoc(res, 0, &maxv, 0, &maxloc);
	std::cout << "maxv: " << maxv << std::endl;

	rectangle(img, Rect(maxloc.x, maxloc.y, templ.cols, templ.rows), Scalar(0, 0, 255), 2);

	imshow("templ", templ);
	imshow("res_norm", res_norm);
	imshow("img", img);
	waitKey();
	destroyAllWindows();
}
void faces() {
	Mat src = imread("../src/kids.png");
	CascadeClassifier classifier("../src/haarcascade_frontalface_default.xml");

	std::vector<Rect> faces;
	classifier.detectMultiScale(src, faces);
	for (Rect rc : faces) {
		rectangle(src, rc, Scalar(255, 0, 255), 2);
	}
	imshow("src", src);
	waitKey();
	destroyAllWindows();
}
void eyes() {
	Mat src = imread("../src/kids.png");
	CascadeClassifier face_classifier("../src/haarcascade_frontalface_default.xml");
	CascadeClassifier eye_classifier("../src/haarcascade_eye.xml");

	std::vector<Rect> faces;
	face_classifier.detectMultiScale(src, faces);
	for (Rect face : faces) {
		rectangle(src, face, Scalar(255, 0, 255), 2);

		Mat faceROI = src(face);
		std::vector<Rect> eyes;
		eye_classifier.detectMultiScale(faceROI, eyes);

		for (Rect eye : eyes) {
			Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
			circle(faceROI, center, eye.width / 2, Scalar(255, 0, 0), 2, LINE_AA);
		}
	}
	imshow("src", src);
	waitKey();
	destroyAllWindows();
}
void hog() {
	VideoCapture cap("../src/vtest.avi");
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	Mat frame;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;
		std::vector<Rect> detected;
		hog.detectMultiScale(frame, detected);
		for (Rect r : detected) {
			Scalar c = Scalar(rand() % 256, rand() % 256, rand() % 256);
			rectangle(frame, r, c, 3);
		}
		imshow("frame", frame);
		if (waitKey(5) == 27)
			break;
	}
}
void qr() {
	VideoCapture cap(0);
	QRCodeDetector detector;

	Mat frame;
	while (true) {
		cap >> frame;
		std::vector<Point> points;

		Mat img;
		String info = detector.detectAndDecode(frame, points, img);

		if (!info.empty()) {
			polylines(frame, points, true, Scalar(0, 0, 255), 2);
			putText(frame, info, Point(10, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
		}
		if (!img.empty()) {
			imshow("img", img);
		}
		imshow("frame", frame);
		if (waitKey(10) == 27)
			break;
	}
}

int main(void) {
#if TEMPLATE == 1
	template_matching();
#endif
#if FACE == 1
	faces();
#endif
#if EYE == 1
	eyes();
#endif
#if HOG == 1
	hog();
#endif
#if QR == 1
	qr();
#endif
}
