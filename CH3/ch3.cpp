#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define POINT 0
#define SIZE 0
#define RECT 0
#define ROTATED 0
#define RANGE 0
#define STRING 0
#define MAT 0
#define MATCOPY 0
#define ROI 0
#define PIXEL 0
#define MATINFO 0
#define MATOP 0
#define MATTRANS 0
#define VEC 0
#define SCALAR 0
#define INPUTARRAY 1
void printMat(InputArray _mat);	//INPUTARRAY���� ���

int main(void) {
#if POINT == 1

	Point pt1;		// initialize 0,0
	cout << "pt1: " << pt1 << endl;
	pt1.x = 5; pt1.y = 10;	// change 5,10
	cout << "pt1: " << pt1 << endl;
	Point pt2(10, 20);	// initialize 10,20
	cout << "pt2: " << pt2 << endl;
	Point pt3 = pt1 + pt2;	// 5+10, 10+20
	cout << "pt3: " << pt3 << endl;
	Point pt4 = pt1 - pt2;	// 5-10, 10-20
	cout << "pt4: " << pt4 << endl;
	Point pt5 = pt1 * 2;	// 5*2, 10*2
	cout << "pt5: " << pt5 << endl;
	int d1 = pt1.dot(pt2); // 5*10 + 10*20, dot product
	cout << "pt1 * pt2: " << d1 << endl;
	bool b1 = (pt1 == pt2);	// comparison
	cout << "pt1 == pt2: " << b1 << endl << endl;

#endif
#if SIZE == 1

	Size s1, s2(10, 20); // initialize 0,0 & 10,20
	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	s1.width = 5; s1.height = 10;	// change 5,10
	cout << "s1: " << s1 << endl;
	Size s3 = s1 + s2;	// 5+10 X 10+20
	cout << "s3: " << s3 << endl;
	Size s4 = s1 * 2;	// 5*2, 10*2
	cout << "s4: " << s4 << endl;
	int area = s1.area(); // 5 * 10 = 50
	cout << "s1 area: " << area << endl;
	Size s1_copy(5, 10);	// init same to s1
	bool b2 = (s1 == s1_copy);	// comparison
	cout << "s1 == s1_cp: " << b2 << endl << endl;

#endif
#if RECT == 1
	Rect rc1;	// rc1 = [0x0 from (0, 0)]
	Rect rc2(10, 10, 60, 40); //rc2 = [60x40 from (10,10)]
	cout << "rc2.tl: " << rc2.tl() << endl; // ���� ��� ��ǥ ���
	cout << "rc2.br: " << rc2.br() << endl; // ���� �ϴ� ��ǥ ���
	cout << "rc2.area: " << rc2.area() << endl; // ���� ��� >> 60 x 40 = 2400
	Rect rc3 = rc1 + Size(50, 40);	// rc3 = [50x40 from (0,0)]
	cout << "rc3.tl: " << rc3.tl() << endl; // ���� ��� ��ǥ ���
	cout << "rc3.br: " << rc3.br() << endl; // ���� �ϴ� ��ǥ ���
	cout << "rc3.area: " << rc3.area() << endl; // ���� ��� >> 50 x 40 = 2000
	Rect rc4 = rc2 + Point(10, 10);	// rc4 = [60x40 from (20,20)]
	cout << "rc4.tl: " << rc4.tl() << endl; // ���� ��� ��ǥ ���
	cout << "rc4.br: " << rc4.br() << endl; // ���� �ϴ� ��ǥ ���
	cout << "rc4.area: " << rc4.area() << endl; // ���� ��� >> 60 x 40 = 2400
	Rect rc5 = rc3 & rc4;	// rc5 = [30x20 from (20, 20)]
	cout << "rc5.tl: " << rc5.tl() << endl; // ���� ��� ��ǥ ���
	cout << "rc5.br: " << rc5.br() << endl; // ���� �ϴ� ��ǥ ���
	cout << "rc5.area: " << rc5.area() << endl; // ���� ��� >> 30 x 20 = 600
	Rect rc6 = rc3 | rc4;	// rc5 = [80x60 from (0, 0)]
	cout << "rc6.tl: " << rc6.tl() << endl; // ���� ��� ��ǥ ���
	cout << "rc6.br: " << rc6.br() << endl; // ���� �ϴ� ��ǥ ���
	cout << "rc6.area: " << rc6.area() << endl; // ���� ��� >> 80 x 60 = 4800
	cout << "rc5: " << rc5 << endl;
	cout << "rc6: " << rc6 << endl << endl;
#endif
#if ROTATED == 1
	RotatedRect rr1(Point2f(40, 30), Size(40, 20), 30.f);	// rr1 = [40x20 from center (40,30) rotate 30 angle]
	Point2f pts[4];
	rr1.points(pts);	// ȸ���� �簢���� 4 �������� ����, ������ ���� �ϴܺ��� �ð����
	cout << "pts: ";
	for (Point2f p : pts)
		cout << p << " ";
	cout << endl;	// ��ǥ 4�� ���
	Rect boundRc = rr1.boundingRect();
	cout << "boundRc: " << boundRc << endl;	// boundingRect ���.
	Rect2f boundRcf = rr1.boundingRect2f();
	cout << "boundRcf: " << boundRcf << endl;	//���� �Ǽ����� ���ϸ� boundingRect2f()���

	RotatedRect rr2(Point2f(0, 0), Point2f(10, 0), Point2f(10, 10));	
	// 3���� ������ �����ϱ� ���ؼ��� �ð������ ���Ѿ��Ѵ�. �� �׷��� ��Ÿ�� ����
	rr2.points(pts);
	cout << "pts: ";
	for (Point2f p : pts)
		cout << p << " ";
	cout << endl << endl;	// ��ǥ 4�� ���, 3 ���� �־����� �� ������ ���� ��� ó���ϴ��� Ȯ���ϱ� ����.
#endif
#if RANGE == 1
	Range r1(0, 10); // 0 ~ 9 ������ ����
	cout << "r1: " << r1 << endl;	// ������ ����Ѵ�. [0 : 10)
	cout << "r1 size: " << r1.size() << endl; // r1�� ���� ũ��
	cout << "r1 empty: " << r1.empty() << endl;	// r1�� start�� end�� ������ true

	Range rMax = Range::all();	// [INT_MIN : INT_MAX) �� range ���
	cout << "rMax: " << rMax << endl << endl;
#endif
#if STRING == 1
	cout << "std::string�� ����" << endl << endl;
#endif
#if MAT == 1
	Mat img1(480, 640, CV_8UC1);	// 640 x 480, unsigned char 1-channel
	Mat img2(480, 640, CV_8UC3);	// 640 x 480, unsinged char 3-channels
	Mat img3(Size(640, 480), CV_8UC3);	
	// Size�� ����, ���η� �Է�, Mat�� ����, ���η� �Է�, ���� 3���� �ʱ�ȭ�� ������ ������ �ʱ�ȭ

	Mat img4(480, 640, CV_8UC1, Scalar(128));	// 640 x 480, �ʱⰪ 128
	Mat img4(480, 640, CV_8UC3, Scalar(0, 0, 255));	// 640 x 480, �ʱⰪ 0,0,255

	Mat mat1 = Mat::zeros(3, 3, CV_32SC1);	// 3x3�� 0 matrix
	Mat mat2 = Mat::ones(3, 3, CV_32FC1);	// 3x3�� 1 matrix
	Mat mat3 = Mat::eye(3, 3, CV_32FC1);	// 3x3�� ���� ���

	float data[] = { 1,2,3,4,5,6 };
	Mat mat4(2, 3, CV_32FC1, data);	// �ܺ� ������ data�� ��� �ʱ�ȭ, 2x3���� �ϴ� [1,2,3
									//												 4,5,6]
	// �޸� �ּ� ����

	Mat_<float> mat5_(2, 3);
	mat5_ << 1, 2, 3, 4, 5, 6;
	Mat mat5 = mat5_;		// Mat_�� ����Ͽ� ���Ҹ� �߰��ϰ� Mat Ŭ������ ��ȯ, ����� ���� ����
	Mat mat6 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);	// �̰͵� ���� ����
	Mat mat7 = Mat_<float>({ 2,3 }, { 1,2,3,4,5,6 });	// �̰͵� ���� ����

	mat4.create(256, 256, CV_8UC3);	
	// �̹� ������ mat ������ ���Ӱ� �ʱ�ȭ�� ��, ���� Ÿ�԰� ũ�Ⱑ �Ȱ����� �״�� �Լ� ����.
	mat5.create(4, 4, CV_32FC1);

	mat4 = Scalar(255, 0, 0);	// ���Ӱ� ��� ���ҿ� value 
	mat5.setTo(1.f);	// �̰͵� ��� value ����
#endif
#if MATCOPY ==1
	Mat dog1 = imread("dog.bmp");
	Mat dog2 = dog1;	// ���� ����
	Mat dog3;
	dog3 = dog1;	//���� ����
	Mat dog4 = dog1.clone();	// ���� ����
	Mat dog5;
	dog1.copyTo(dog5);	// ���� ����

	dog1.setTo(Scalar(0, 255, 255));	//src1�� ��� ���Ҹ� 0,255,255�� ����

	imshow("dog1", dog1);
	imshow("dog2", dog2);
	imshow("dog3", dog3);
	imshow("dog4", dog4);
	imshow("dog5", dog5);

	waitKey();
	destroyAllWindows();
#endif
#if ROI == 1
	Mat cat1 = imread("cat.bmp");
	Mat cat2 = cat1(Rect(220, 120, 340, 240));			// ���� ����
	Mat cat3 = cat1(Rect(220, 120, 340, 240)).clone();	// ���� ����
	Mat cat4 = cat1.rowRange(Range(0, 150));	// rowRange�� ���� ����
	Mat cat5 = cat1.colRange(200, 500);	// colRange�� ���� ����
	Mat cat6 = cat1(Range(120, 360), Range(220, 560));	// Range�� ����
	cat2 = ~cat2;	// �ش� �޸� �� �ٲ�

	imshow("cat1", cat1);
	imshow("cat2", cat2);
	imshow("cat3", cat3);
	imshow("cat4", cat4);
	imshow("cat5", cat5);
	imshow("cat6", cat6);
	waitKey();
	destroyAllWindows();
#endif
#if PIXEL == 1
	Mat mat8 = Mat::zeros(3, 4, CV_8UC1);
	//���� ����: at ���, ������ ��ġ ���� ����
	for (int j = 0; j < mat8.rows; j++)
		for (int i = 0; i < mat8.cols; i++)
			mat8.at<uchar>(j, i)++;	// y,x �������� ����, uchar�� ���� type�� ����ؾ���.
	cout << "mat8 by at\n" << mat8 << endl;
	//���� ����: ptr ���, �������� ������ ��ġ ���� �Ұ�
	for (int j = 0; j < mat8.rows; j++) {
		uchar* p = mat8.ptr<uchar>(j);	//j��° row ������
		for (int i = 0; i < mat8.cols; i++) {
			p[i]++;	//�����ͷ� ���� ����
		}
	}
	cout << "mat8 by ptr\n" << mat8 << endl;
	//���� ����: MatIterator_���, ������ ������ ó������ ������ ����
	for (MatIterator_<uchar>it = mat8.begin<uchar>(); it != mat8.end<uchar>(); it++)
		(*it)++;
	cout << "mat8 by MatIterator\n" << mat8 << endl << endl;
#endif
#if MATINFO == 1
	Mat lenna1 = imread("lenna.bmp");
	cout << "Width: " << lenna1.cols << endl;	// �ʺ�
	cout << "Height: " << lenna1.rows << endl;	// ����
	cout << "Channels: " << lenna1.channels() << endl;	// ä�� ��
	cout << "Type: " << lenna1.type() << endl;	// ���� (��) CV_8U, CV_32F
	if (lenna1.type() == CV_8UC1)
		cout << "lenna is a grayscale image." << endl;
	else if (lenna1.type() == CV_8UC3)
		cout << "lenna is a RGBscale image." << endl;
	cout << "ElemSize: " << lenna1.elemSize() << endl;	// �� ���� ���Ұ� �����ϴ� �޸� ũ��
	cout << "ElemSize1: " << lenna1.elemSize1() << endl;	// �� ä�ο��� �� ���� ���Ұ� �����ϴ� �޸� ũ��
	cout << "Empty: " << lenna1.empty() << endl;	//����ִ��� Ȯ��
	cout << "isContinuous: " << lenna1.isContinuous() << endl;	//�� ���� ���Ұ� ���������� ����Ǿ� �ִ���
	cout << "isSubMatrix(origin): " << lenna1.isSubmatrix() << endl;	//����� �ٸ� ����� �κ� �������
	cout << "isSubMatrix(ROI): " << lenna1(Rect(100, 120, 100, 100)).isSubmatrix() << endl; //ROI�� ���ؼ� SubMatrix ����
	cout << "Size: " << lenna1.size() << endl;	// ��� ũ��
	cout << "Total: " << lenna1.total() << endl;// ��� ��ü ���� ����

	float data[] = { 2.f, 1.414f, 3.f, 1.732f };
	Mat mat9(2, 2, CV_32FC1, data);
	cout << "mat9\n" << mat9 << endl << endl; // ��� ���Ҵ� <<�� ��� ����
#endif
#if MATOP == 1
	Mat matop1 = Mat::zeros(3, 3, CV_32FC1);	// 3x3�� 0 matrix
	Mat matop2 = Mat::ones(3, 3, CV_32FC1);	// 3x3�� 1 matrix
	Mat matop3 = Mat::eye(3, 3, CV_32FC1);	// 3x3�� ���� ���
	Mat matop4 = Mat_<float>({ 3,2 }, { 2,0,0,3,1,1 });	//3x2 ���
	Mat matop5 = Mat_<float>({ 3,3 }, { 2,-1,0,1,0,-1,1,0,1 });	//3x3 ���
	Scalar sop1 = Scalar(5);	// Scalar �� ����
	double dop1 = 2.5;	// double ���� ����
	cout << "matop2 + matop3\n" << matop2 + matop3 << endl;
	cout << "matop1 - matop3\n" << matop1 - matop3 << endl;
	cout << "sop1 + matop3\n" << sop1 + matop3 << endl;	// ��� ���ҿ� ����
	cout << "-matop2\n" << -matop2 << endl;
	cout << "matop2 * dop1\n" << matop2 * dop1 << endl;	
	cout << "matop3 / dop1\n" << matop3 / dop1 << endl;
	cout << "matop2 / matop3\n" << matop2 / matop3 << endl;
	cout << "matop2 * matop4\n" << matop2 * matop4 << endl;	// ��� ���� ��Ÿ��
	cout << "matop2 mul matop3\n" << matop2.mul(matop3) << endl;	// ���� ��ġ�� ���ҳ��� ��
	cout << "matop5 inverse\n" << matop5.inv() << endl;	//��� �����
	cout << "matop4 transpose\n" << matop4.t() << endl; //��ġ���
#endif
#if MATTRANS ==1
	Mat lenna2 = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat img1f;
	lenna2.convertTo(img1f, CV_32FC1);	// CV_8UC1 -> CV_32FC1���� ��ȯ

	uchar data2[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	Mat uMat1(3, 4, CV_8UC1, data2);
	Mat uMat2 = uMat1.reshape(0, 1);	// ä�� �� ��ȭ X, �� �� 1
	cout << "uMat1:\n" << uMat1 << endl;
	cout << "uMat2:\n" << uMat2 << endl;

	uMat1.resize(5, 100);	//�� ���� 5, �߰��Ǵ� ������ �ʱ갪 100
	cout << "uMat1:\n" << uMat1 << endl;

	Mat uMat3 = Mat::ones(1, 4, CV_8UC1) * 250;	// 1x4 CV_8UC1 ��� ����
	uMat1.push_back(uMat3);	//5x4 ��Ŀ� 1x4��� �߰�
	cout << "uMat1:\n" << uMat1 << endl;

	uMat1.pop_back(2);	// 6x4 ��Ŀ��� �Ʒ� 2�� ����
	cout << "uMat1:\n" << uMat1 << endl;

#endif
#if VEC == 1
	Vec<uchar, 3> p1, p2(0, 0, 255);	// uchar �ڷ��� �� ���� ������ Vec Ŭ���� ����
	Vec3b p3, p4(0, 0, 255);	//���� ����
	p1.val[0] = 100;	// ù��° ���Ҹ� �ʱ�ȭ
	p1[0] = 100;	// ���� ����
	cout << "p1: " << p1 << endl;
	cout << "p2: " << p2 << endl << endl;
#endif
#if SCALAR == 1
	Scalar gray = 128;	// ��⸸ ����
	cout << "gray: " << gray << endl;

	Scalar yellow(0, 255, 255);	// BGR ������ ����
	cout << "yellow: " << yellow << endl;

	Mat yellowImg(256, 256, CV_8UC3, yellow);	// 256x256 yellow ����� ����
	imshow("Yellow", yellowImg);

	for (int i = 0; i < 4; i++)
		cout << yellow[i] << endl;	// Scalar ä�� ����, 4��° ���Ҵ� �ڵ����� 0�ʱ�ȭ
	cout << endl;
	waitKey();
	destroyAllWindows();
#endif
#if INPUTARRAY == 1
	uchar data3[] = { 1,2,3,4,5,6 };
	Mat mat10(2, 3, CV_8U, data3);
	printMat(mat10);

	vector<float> vec1 = { 1.2f,3.4f,-2.1f };
	printMat(vec1);
#endif
return 0;
}

void printMat(InputArray _mat) {
	Mat mat = _mat.getMat();	// InputArray�� �޾ƿͼ� getMat()���� ������ ��ȯ
	cout << mat << endl;
}