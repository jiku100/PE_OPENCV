#include <opencv2/opencv.hpp>
#include <iostream>

#define DEBUG 1

using namespace std;
using namespace cv;

// Point
#if DEBUG == 0
int main(void) {
	Point pt1;		// initialize 0,0
	cout << "pt1: " << pt1 << endl;
	pt1.x = 5; pt1.y = 10;	// change 5,10
	cout << "pt1: " << pt1 << endl;
	Point pt2(10, 20);	// initialize 10,20
	cout << "pt2: " << pt2 << endl;
	Point pt3 = pt1 + pt2;	// 5+10, 10+20
	cout << "pt3: " << pt3 << endl;
	Point pt4 = pt1 * 2;	// 5*2, 10*2
	cout << "pt4: " << pt4 << endl;
	int d1 = pt1.dot(pt2); // 5*10 + 10*20, dot product
	cout << "pt1 * pt2: " << d1 << endl;
	bool b1 = (pt1 == pt2);	// comparison
	cout << "pt1 == pt2: " << b1 << endl;
	return 0;
}
#endif

//Size
#if DEBUG == 1
int main(void) {
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
	bool b1 = (s1 == s1);	// comparison
	cout << "s1 == s1_cp: " << b1 << endl;
	return 0;
}
#endif

//Rect
#if DEBUG == 2

#endif