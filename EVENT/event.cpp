#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img1;
Point ptOld;
void on_Mouse(int event, int x, int y, int flags, void*);	// ���콺 �ݹ� �Լ�
void on_level_change(int pos, void* userdata);	// Ʈ���� �ݹ� �Լ�

int main(void) {
	img1 = imread("../src/lenna.bmp");

	// Ű���� �Է�
	namedWindow("img1");
	imshow("img1", img1);
	while (true) {
		// waitKey()�� Ű���� �Է� ó��, ���� F1 ~ F12, ����Ű���� �ϱ� ���ؼ��� waitKeyEx() ���
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

	// ���콺 �̺�Ʈ
	namedWindow("img");
	setMouseCallback("img", on_Mouse);	// ���콺 �ݹ� �Լ� ����
	imshow("img", img1);
	waitKey();
	destroyAllWindows();

	// Ʈ����
	Mat img2 = Mat::zeros(400, 400, CV_8UC1);
	namedWindow("image");
	createTrackbar("level", "image", 0, 16, on_level_change, (void*)&img2);
	imshow("image", img2);
	waitKey();
	destroyAllWindows();
	return 0;
}
void on_Mouse(int event, int x, int y, int flags, void*) {	// ���콺 �ݹ� �Լ�
	switch (event)
	{
	case EVENT_LBUTTONDOWN:	// ���� ��ư ���� ��
		ptOld = Point(x, y);
		cout << "EVENT_LBUTTONDOWN: " << x << ", " << y << endl;
		break;
	case EVENT_LBUTTONUP:	// ���� ��ư �� ��
		cout << "EVENT_LBUTTONUP: " << x << ", " << y << endl;
		break;
	case EVENT_MOUSEMOVE:	// ���콺�� ������ ��
		if (flags & EVENT_FLAG_LBUTTON) {	// ������ ������ ������
			line(img1, ptOld, Point(x, y), Scalar(0, 255, 255), 2);
			imshow("img", img1);
			ptOld = Point(x, y);
		}
		break;
	default:
		break;
	}
}

void on_level_change(int pos, void* userdata) {	// Ʈ���� �Լ�
	Mat img = *(Mat*)userdata;	// void*�� ���� ���� Mat* �� �ٲ㼭 ��������

	img.setTo(pos * 16);
	imshow("image", img);
}