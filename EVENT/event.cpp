#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img1;
Point ptOld;
void on_Mouse(int event, int x, int y, int flags, void*);	// 마우스 콜백 함수
void on_level_change(int pos, void* userdata);	// 트랙바 콜백 함수

int main(void) {
	img1 = imread("../src/lenna.bmp");

	// 키보드 입력
	namedWindow("img1");
	imshow("img1", img1);
	while (true) {
		// waitKey()로 키보드 입력 처리, 만약 F1 ~ F12, 방향키까지 하기 위해서는 waitKeyEx() 사용
		int keyCode = waitKey();	
		if (keyCode == 'i' || keyCode == 'I') {
			img1 = ~img1;
			cout << "Press i" << endl;
		}
		else if (keyCode == 'q' || keyCode == 'Q' || keyCode == 27)
			break;
		imshow("img1", img1);
	}
	destroyAllWindows();

	// 마우스 이벤트
	namedWindow("img");
	setMouseCallback("img", on_Mouse);	// 마우스 콜백 함수 설정
	imshow("img", img1);
	waitKey();
	destroyAllWindows();

	// 트랙바
	Mat img2 = Mat::zeros(400, 400, CV_8UC1);
	namedWindow("image");
	createTrackbar("level", "image", 0, 16, on_level_change, (void*)&img2);
	imshow("image", img2);
	waitKey();
	destroyAllWindows();
	return 0;
}
void on_Mouse(int event, int x, int y, int flags, void*) {	// 마우스 콜백 함수
	switch (event)
	{
	case EVENT_LBUTTONDOWN:	// 왼쪽 버튼 누를 때
		ptOld = Point(x, y);
		cout << "EVENT_LBUTTONDOWN: " << x << ", " << y << endl;
		break;
	case EVENT_LBUTTONUP:	// 왼쪽 버튼 땔 때
		cout << "EVENT_LBUTTONUP: " << x << ", " << y << endl;
		break;
	case EVENT_MOUSEMOVE:	// 마우스가 움직일 때
		if (flags & EVENT_FLAG_LBUTTON) {	// 왼쪽이 눌려져 있으면
			line(img1, ptOld, Point(x, y), Scalar(0, 255, 255), 2);
			imshow("img", img1);
			ptOld = Point(x, y);
		}
		break;
	default:
		break;
	}
}

void on_level_change(int pos, void* userdata) {	// 트랙바 함수
	Mat img = *(Mat*)userdata;	// void*로 들어온 값을 Mat* 로 바꿔서 간접참조

	img.setTo(pos * 16);
	imshow("image", img);
}