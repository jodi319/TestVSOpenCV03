//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//static void help()
//{
//	cout << "\nThis program demonstrated the floodFill() function\n"
//		"Call:\n"
//		"./ffilldemo [image_name -- Default: fruits.jpg]\n" << endl;
//
//	cout << "Hot keys: \n"
//		"\tESC - quit the program\n"
//		"\tc - switch color/grayscale mode\n"
//		"\tm - switch mask mode\n"
//		"\tr - restore the original image\n"
//		"\ts - use null-range floodfill\n"
//		"\tf - use gradient floodfill with fixed(absolute) range\n"
//		"\tg - use gradient floodfill with floating(relative) range\n"
//		"\t4 - use 4-connectivity mode\n"
//		"\t8 - use 8-connectivity mode\n" << endl;
//}
//
//Mat image0, image, gray, mask,histImage;
//int ffillMode = 1;
//int loDiff = 100, upDiff = 100;
//int connectivity = 4;
//int isColor = true;
//bool useMask = false;
//int newMaskVal = 255;
//
////static void MySeed(int x, int y)
////{
////	Point seed = Point(x, y);
////	int lo = ffillMode == 0 ? 0 : loDiff;
////	int up = ffillMode == 0 ? 0 : upDiff;
////	int flags = connectivity + (newMaskVal << 8) +
////		(ffillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
////	int b = (unsigned)theRNG() & 255;
////	int g = (unsigned)theRNG() & 255;
////	int r = (unsigned)theRNG() & 255;
////	Rect ccomp;
////
////	Scalar newVal = isColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.114);
////	Mat dst = isColor ? image : gray;
////	int area;
////
////	if (useMask)
////	{
////		threshold(mask, mask, 1, 128, CV_THRESH_BINARY);
////		area = floodFill(dst, mask, seed, newVal, &ccomp, Scalar(lo, lo, lo),
////			Scalar(up, up, up), flags);
////		imshow("mask", mask);
////	}
////	else
////	{
////		area = floodFill(dst, seed, newVal, &ccomp, Scalar(lo, lo, lo),
////			Scalar(up, up, up), flags);
////	}
////
////	imshow("image", dst);
////	cout << area << " pixels were repainted\n";
////}
////static void onMouse(int event, int x, int y, int, void*)
////{
////	if (event != CV_EVENT_LBUTTONDOWN)
////		return;
////
////	Point seed = Point(x, y);
////	int lo = ffillMode == 0 ? 0 : loDiff;
////	int up = ffillMode == 0 ? 0 : upDiff;
////	int flags = connectivity + (newMaskVal << 8) +
////		(ffillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
////	int b = (unsigned)theRNG() & 255;
////	int g = (unsigned)theRNG() & 255;
////	int r = (unsigned)theRNG() & 255;
////	Rect ccomp;
////
////	Scalar newVal = isColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.114);
////	Mat dst = isColor ? image : gray;
////	int area;
////
////	if (useMask)
////	{
////		/*  5 types of Thresholding operations
////		0: Binary
////		1: Binary Inverted
////		2: Threshold Truncated
////		3: Threshold to Zero
////		4: Threshold to Zero Inverted
////		*/
////		threshold(mask, mask, 1, 128, CV_THRESH_BINARY);	//(input, output, thres_value, max_thres_value, thres_type)
////		area = floodFill(dst, mask, seed, newVal, &ccomp, Scalar(lo, lo, lo),
////			Scalar(up, up, up), flags);
////		imshow("mask", mask);
////	}
////	else
////	{
////		area = floodFill(dst, seed, newVal, &ccomp, Scalar(lo, lo, lo),
////			Scalar(up, up, up), flags);
////	}
////
////	imshow("image", dst);
////	cout << area << " pixels were repainted\n";
////}
//
//
//int main(int argc, char** argv)
//{
//	char* filename = argc >= 2 ? argv[1] : (char*)"20140612_MINEGARDEN_SURVEY_sds_UseRawDataSetting_01_18_30_CylindricalMine01.jpg";
//	image0 = imread(filename, 1);
//
//	if (image0.empty())
//	{
//		cout << "Image empty. Usage: ffilldemo <image_name>\n";
//		return 0;
//	}
//	help();
//	char* source_window = "Source image";
//	char* equalized_window = "Equalized Image";
//
//	/// Convert to grayscale
//	cvtColor(image0, gray, CV_BGR2GRAY);
//
//	/// Apply Histogram Equalization
//	equalizeHist(gray, histImage);
//
//	/// Display results
//	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
//	namedWindow(equalized_window, CV_WINDOW_AUTOSIZE);
//
//	imshow(source_window, image0);
//	imshow(equalized_window, histImage);
//
//	//------------------------------------------------------------
//	// Initialize parameters
//	int histSize = 256;    // bin size
//	float range[] = { 0, 255 };
//	const float *ranges[] = { range };
//
//	// Calculate histogram
//	MatND hist;
//	calcHist(&gray, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);
//
//	// Show the calculated histogram in command window
//	double total;
//	total = gray.rows * gray.cols;
//	for (int h = 0; h < histSize; h++)
//	{
//		float binVal = hist.at<float>(h);
//		cout << " " << binVal;
//	}
//
//	// Plot the histogram
//	int hist_w = 512; int hist_h = 400;
//	int bin_w = cvRound((double)hist_w / histSize);
//
//	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
//	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
//
//	for (int i = 1; i < histSize; i++)
//	{
//		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
//			Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
//			Scalar(255, 0, 0), 2, 8, 0);
//	}
//
//	namedWindow("Result", 1);    imshow("Result", histImage);
//	//------------------------------------------------------------
//	/// Wait until user exits the program
//	waitKey(0);
//	return 0;
//}
