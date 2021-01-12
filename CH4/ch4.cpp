#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define CAMERAIN 0
#define VIDEOIN 0
#define VIDEOWRITER 0
#define DRAWLINE 0
#define DRAWSHAPE 0
#define DRAWTEXT 1
int main(void) {
#if CAMERAIN == 1
	VideoCapture cap1(0, CAP_ANY);	// 0 이면 웹캠
	if (!cap1.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return 0;
	}

	cout << "Frame Width: " << cvRound(cap1.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame Height: " << cvRound(cap1.get(CAP_PROP_FRAME_HEIGHT)) << endl;

	Mat frame1, inversed1;
	while (true) {
		cap1 >> frame1;
		if (frame1.empty())
			break;
		inversed1 = ~frame1;
		imshow("frame1", frame1);
		imshow("inversed1", inversed1);

		if (waitKey(10) == 27)
			break;
	}
	destroyAllWindows();

#endif
#if VIDEOIN == 1
	VideoCapture cap2("stopwatch.avi");
	if (!cap2.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return 0;
	}
	cout << "Frame Width: " << cvRound(cap2.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame Height: " << cvRound(cap2.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame count: " << cvRound(cap2.get(CAP_PROP_FRAME_COUNT)) << endl;

	double fps = cap2.get(CAP_PROP_FPS);
	cout << "FPS: " << fps << endl;
	int delay = cvRound(1000 / fps);	// fps로 delay 구함

	Mat frame2, inversed2;
	while (true) {
		cap2 >> frame2;
		if (frame2.empty())
			break;
		inversed2 = ~frame2;
		imshow("frame2", frame2);
		imshow("inversed2", inversed2);

		if (waitKey(delay) == 27)	// delay 구한 것으로 waitKey
			break;
	}
	destroyAllWindows();
#endif
#if VIDEOWRITER == 1
	VideoCapture cap3(0);
	if (!cap3.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return 0;
	}

	int w = cvRound(cap3.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap3.get(CAP_PROP_FRAME_HEIGHT));
	double fps = cap3.get(CAP_PROP_FPS);
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');	// 코덱 설정
	int delay = cvRound(1000 / fps);

	VideoWriter outputVideo1("output.avi", fourcc, fps, Size(w, h));
	if (!outputVideo1.isOpened()) {
		cout << "File open failed!" << endl;
		return 0;
	}

	Mat frame3, inversed3;
	while (true) {
		cap3 >> frame3;
		if (frame3.empty())
			break;
		inversed3 = ~frame3;
		outputVideo1 << inversed3;
		imshow("frame1", frame3);
		imshow("inversed1", inversed3);

		if (waitKey(delay) == 27)
			break;
	}
	destroyAllWindows();
#endif
#if DRAWLINE == 1
	Mat img1(400, 400, CV_8UC3, Scalar(255, 255, 255));

	// 50,50 -> 200,50 으로 색깔 빨간색 줄
	line(img1, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));		
	// shift가 1이니 좌표값을 반절로, 50,70 -> 200,70 으로 검정색 줄
	line(img1, Point(100, 140), Point(400, 140), Scalar(0, 0, 0), 1, 8, 1); 
	// 50,100 -> 200,100 으로 색깔 보라색, 두께 3
	line(img1, Point(50, 100), Point(200, 100), Scalar(255, 0, 255), 3);	
	// 50,150 -> 200,150 으로 색깔 파란색, 두께 10
	line(img1, Point(50, 150), Point(200, 150), Scalar(255, 0, 0), 10);	

	// 250,50 -> 350,100 으로 색깔 빨간색 줄, 두께 1, LINE_4 방법
	line(img1, Point(250, 50), Point(350, 100), Scalar(0, 0, 255), 1, LINE_4);
	// 250,70 -> 350,120 으로 색깔 보라색, 두께 1, LINE_8 방법
	line(img1, Point(250, 70), Point(350, 120), Scalar(255, 0, 255), 1, LINE_8);
	// 250,90 -> 350,140 으로 색깔 파란색, 두께 1, 안티엘리어싱 방법
	line(img1, Point(250, 90), Point(350, 140), Scalar(255, 0, 0), 1, LINE_AA);

	// 50,200 -> 150,200 으로 색깔 빨간색, 두께 1, 화살표 0.1 비율
	arrowedLine(img1, Point(50, 200), Point(150, 200), Scalar(0, 0, 255), 1);	
	// 50,250 -> 350,250 으로 색깔 보라색, 두께 1, 화살표 0.1 비율
	arrowedLine(img1, Point(50, 250), Point(350, 250), Scalar(255, 0, 255), 1);	
	//50,300 -> 350,300 으로 색깔 파란색, 두께 1, LINE_8 방법, 쉬프트 0, 화살표 0.05 비율
	arrowedLine(img1, Point(50, 300), Point(350, 300), Scalar(255, 0, 0), 1, LINE_8, 0, 0.05);	

	drawMarker(img1, Point(50, 350), Scalar(0, 0, 255), MARKER_CROSS);	// 50,350에 빨간색 십자가
	drawMarker(img1, Point(100, 350), Scalar(0, 0, 255), MARKER_TILTED_CROSS);	// 100,350에 빨간색 회전 십자가
	drawMarker(img1, Point(150, 350), Scalar(0, 0, 255), MARKER_STAR);	// 150,350에 빨간색 별
	drawMarker(img1, Point(200, 350), Scalar(0, 0, 255), MARKER_DIAMOND);	// 200,350에 빨간색 마름모
	drawMarker(img1, Point(250, 350), Scalar(0, 0, 255), MARKER_SQUARE);	// 250,350에 빨간색 사각형
	drawMarker(img1, Point(300, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_UP);	// 300,350에 빨간색 위 삼각형
	drawMarker(img1, Point(350, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_DOWN);	// 350,350에 빨간색 아래 삼각형

	imshow("img1", img1);
	waitKey();
	destroyAllWindows();
#endif
#if DRAWSHAPE == 1
	Mat img2(400, 400, CV_8UC3, Scalar(255, 255, 255));

	// 50,50 에서 100x50크기로 두께 2 빨간색 사각형
	rectangle(img2, Rect(50, 50, 100, 50), Scalar(0, 0, 255), 2);	
	// 50,150 에서 100x50크기로 내부 꽉찬 진한 빨간색 사각형
	rectangle(img2, Rect(50, 150, 100, 50), Scalar(0, 0, 128), -1);	

	// 300,120 중심, 반지름 30 짜리 민트색 속 꽉찬 원
	circle(img2, Point(300, 120), 30, Scalar(255, 255, 0), -1, LINE_AA);
	//300,120 중심, 반지름 60 짜리 두께 3 파란색 원
	circle(img2, Point(300, 120), 60, Scalar(255, 0, 0), 3, LINE_AA);	

	//타원 그리기 시작은 중심으로 +x 축 방향부터
	// 120,300 중심 x축 반지름 60, y축 반지름 30, 회전 각도 20, 0 ~ 270도 민트색 속 꽉찬 타원
	ellipse(img2, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(255, 255, 0), -1, LINE_AA);	
	// 120,300 중심 x축 반지름 100, y축 반지름 50, 회전 각도 20, 0 ~ 360도 초록색 두께 2 타원
	ellipse(img2, Point(120, 300), Size(100, 50), 20, 0, 360, Scalar(0, 255, 0), 2, LINE_AA);	

	vector<Point> pts;
	pts.push_back(Point(250, 250)); 	pts.push_back(Point(300, 250)); 	pts.push_back(Point(300, 300));
	pts.push_back(Point(350, 300)); 	pts.push_back(Point(350, 350)); 	pts.push_back(Point(250, 350));
	polylines(img2, pts, true, Scalar(255, 0, 255), 2);	// pts에 저장된 점들을 가지고 보라색 두께 2 다각형

	imshow("img2", img2);
	waitKey();
	destroyAllWindows();
#endif
#if DRAWTEXT == 1
	Mat img3(200, 640, CV_8UC3, Scalar(255, 255, 255));

	const String text = "Hello, OpenCV";
	int fontFace = FONT_HERSHEY_TRIPLEX;
	double fontScale = 2.0;
	int thickness = 1;

	Size sizeText = getTextSize(text, fontFace, fontScale, thickness, 0);	// test의 크기를 구함
	Size sizeImg = img3.size();

	Point org((sizeImg.width - sizeText.width) / 2, (sizeImg.height + sizeText.height) / 2);	// 텍스트를 위치시킬 왼쪽 아래 좌표를 구함

	putText(img3, text, org, fontFace, fontScale, Scalar(255, 0, 0), thickness);
	// org가 텍스트의 왼쪽 아래 좌표이기 때문에 width는 더하고 heigth는 빼서 좌표를 정한다.
	rectangle(img3, org, org + Point(sizeText.width, -sizeText.height), Scalar(255, 0, 0), 1);

	imshow("img3", img3);
	waitKey();
	destroyAllWindows();
#endif
	return 0;
}