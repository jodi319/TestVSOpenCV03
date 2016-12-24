//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//
//using namespace std;
//
//int xDim, yDim, zDim;
//float ThreshHold = 45.0;
//unsigned long total[3];
//int coont, tt;
//IplImage *Image1;
//IplImage *Image2;
//
//CvScalar s = cvScalar(0, 0, 0, 0);
//CvScalar s11 = cvScalar(0, 0, 0, 0);
//
//int Diff, mean[3], temp[3];
//
//void GrowColor(int x, int y);
//
//int main(int argc, char *argv[]) {
//
//	char value[4];
//
//	int pixType, dimCut;
//	int Dbug = false;
//	int Xseed = 40, Yseed = 234;
//	int i = 0, x, y;
//	Image1 = cvLoadImage("lena.jpg");
//	yDim = Image1->height;
//	xDim = Image1->width;
//	// int step= Image1->widthStep;
//	//uchar* data = (uchar *)Image1->imageData;
//
//	//New image
//	Image2 = cvCreateImage(cvSize(Image1->width, Image1->height), IPL_DEPTH_8U,
//		1);
//	cvZero(Image2);
//	total[0] = total[1] = total[2] = coont = 0;
//
//	//Process
//
//	for (y = Yseed - 5; y <= Yseed + 5; y++)
//		for (x = Xseed - 5; x <= Xseed + 5; x++)
//			if ((x > 0) && (y > 0) && (x < xDim) && (y < yDim)) {
//
//				coont++;
//				s = cvGet2D(Image1, x, y);
//				total[0] += abs(s.val[0]);
//				total[1] += abs(s.val[1]);
//				total[2] += abs(s.val[2]);
//
//			}
//
//	GrowColor(Xseed, Yseed);
//	cvNamedWindow("wndname", 1);
//	cvShowImage("original", Image1);
//
//	cvShowImage("wndname", Image2);
//	cvWaitKey(0);
//	return 0;
//
//}
//
//void GrowColor(int x, int y) {
//	//Check to see if point already part of region
//
//	s.val[0] = 0;
//	s.val[1] = 0;
//	s.val[2] = 0;
//	s.val[3] = 0;
//	if ((x < 1) && (y < 1))
//		s = cvGet2D(Image2, x, y);
//
//	if (s.val[0] == 0) {
//		int k;
//		if ((x == 1) && (y == 1))
//			s11 = cvGet2D(Image1, x, y);
//		mean[0] = total[0] / coont;
//		mean[1] = total[1] / coont;
//		mean[2] = total[2] / coont;
//
//		temp[0] = abs(s11.val[0]) - mean[0];
//		temp[1] = abs(s11.val[1]) - mean[1];
//		temp[2] = abs(s11.val[2]) - mean[2];
//
//		Diff =
//			(int)(sqrt(
//			(temp[0] * temp[0] + temp[1] * temp[1]
//				+ temp[2] * temp[2]) / 3));
//
//		if (Diff < ThreshHold) {
//
//			total[0] += abs(s11.val[0]);
//			total[1] += abs(s11.val[1]);
//			total[2] += abs(s11.val[2]);
//			coont++;
//			s.val[0] = 120;
//			if ((x > 0) && (y > 0))
//				cvSet2D(Image2, x, y, s);
//			if (x > 2)
//				GrowColor(x - 1, y);
//			if (y > 2)
//				GrowColor(x, y - 1);
//			if (x < xDim - 2)
//				GrowColor(x + 1, y);
//			if (y < yDim - 2)
//				GrowColor(x, y + 1);
//
//		}
//
//	}
//
//}