////#include "stdafx.h"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
//
//using namespace cv;
//using namespace std;
//
//int threshold_value = 0;
//int threshold_type = 3;;
//int const max_value = 255;
//int const max_type = 4;
//int const max_BINARY_value = 255;
//Mat tDst,gray,img,heDst;
//char* window_name = "Threshold Demo";
//char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
//char* trackbar_value = "Value";
//void Threshold_Demo(int, void*);
//int var1 = 1;
//Point pos;
//int radius = 7;
////For Canny
//int edgeThresh = 1;
//int lowThreshold;
//int const max_lowThreshold = 100;
//int ratio = 3;
//int kernel_size = 3;
//Mat Cdst, detected_edges;
//const char* Canny_window_name = "Edge Map";
//
//static void CannyThreshold(int, void*)
//{
//	//![reduce_noise]
//	/// Reduce noise with a kernel 3x3
//	blur(gray, detected_edges, Size(3, 3));
//	//![reduce_noise]
//
//	//![canny]
//	/// Canny detector
//	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
//	//![canny]
//
//	/// Using Canny's output as a mask, we display our result
//	//![fill]
//	Cdst = Scalar::all(0);
//	//![fill]
//
//	//![copyto]
//	img.copyTo(Cdst, detected_edges);
//	//![copyto]
//
//	//![display]
//	imshow(window_name, Cdst);
//	//![display]
//}

//int main(int argc, const char** argv)
//{
//	img = imread("20140612_MINEGARDEN_SURVEY_sds_UseRawDataSetting_01_18_30_CylindricalMine01.jpg", CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "MyPic.JPG" and store it in 'img'
//
//	if (img.empty()) //check whether the image is loaded or not
//	{
//		cout << "Error : Image cannot be loaded..!!" << endl;
//		system("pause"); //wait for a key press
//		return -1;
//	}
//
//	//namedWindow("Original image", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
//	//imshow("Original image", img); //display the image which is stored in the 'img' in the "MyWindow" window
//
//	//Convert image to gray-scale
//	cvtColor(img, gray, CV_BGR2GRAY);
//
//	//Sobel Edge Detection
//	Mat sobelx;
//	Sobel(gray, sobelx, CV_32F, 1, 0);
//	double minVal, maxVal;
//	minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
//	cout << "minVal : " << minVal << endl << "maxVal : " << maxVal << endl;
//	Mat drawS;
//	sobelx.convertTo(drawS, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
//	//Plot Sobel
//	//namedWindow("Sobel", CV_WINDOW_AUTOSIZE);
//	//imshow("Sobel", drawS);
//
//
//	//Canny Edge Detection
//	//![create_mat]
//	/// Create a matrix of the same type and size as src (for dst)
//	Cdst.create(img.size(), img.type());
//	//![create_mat]
//	//![create_window]
//	namedWindow(Canny_window_name, WINDOW_AUTOSIZE);
//	//![create_window]
//	//![create_trackbar]
//	/// Create a Trackbar for user to enter threshold
//	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
//	//![create_trackbar]
//	/// Show the image
//	CannyThreshold(0, 0);
//	Mat drawC, edge;
//	//////Canny(gray, edge, 50, 150, 3);
//	//////edge.convertTo(drawC, CV_8U);
//	//Plot Sobel
//	//namedWindow("canny", CV_WINDOW_AUTOSIZE);
//	//imshow("canny", drawC);
//
//	//Histogram Calculation
//	//namedWindow("Gray", 1);    //imshow("Gray", gray);
//	// Initialize parameters
//	int histSize = 256;    // bin size
//	float range[] = { 0, 255 };
//	const float *ranges[] = { range };
//	// Calculate histogram
//	MatND hist;
//	calcHist(&gray, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);
//	// Show the calculated histogram in command window
//	double total;
//	total = gray.rows * gray.cols;
//	for (int h = 0; h < histSize; h++)
//	{
//		float binVal = hist.at<float>(h);
//		cout << " " << binVal;
//	}
//	// Plot the histogram
//	int hist_w = 512; int hist_h = 400;
//	int bin_w = cvRound((double)hist_w / histSize);
//	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
//	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
//	for (int i = 1; i < histSize; i++)
//	{
//		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
//			Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
//			Scalar(255, 0, 0), 2, 8, 0);
//	}
//	//namedWindow("Histogram", 1);    //imshow("Histogram", histImage);
//
//	//Edge detection using Laplacian operator	
//	Mat gDst,lDst, abs_dst;
//	/// Remove noise by blurring with a Gaussian filter
//	GaussianBlur(img, gDst, Size(3, 3), 0, 0, BORDER_DEFAULT);
//	/// Apply Laplace function
//	Laplacian(gray, lDst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
//	convertScaleAbs(lDst, abs_dst);
//	//imshow("Laplacian", abs_dst);
//
//
//	//Histogram Equalization
//	equalizeHist(gray, heDst);
//
//	namedWindow("Original image", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
//	imshow("Original image", img); //display the image which is stored in the 'img' in the "MyWindow" window
//	//namedWindow("Sobel", CV_WINDOW_AUTOSIZE);
//	//imshow("Sobel", drawS);
//	//namedWindow("canny", CV_WINDOW_AUTOSIZE);
//	//imshow("canny", drawC);
//	//namedWindow("Gray", 1);    
//	//imshow("Gray", gray);
//	//namedWindow("Histogram", 1);    
//	//imshow("Histogram", histImage);	
//	//namedWindow("Histogram Equalization", CV_WINDOW_AUTOSIZE);
//	//imshow("Histogram Equalization", heDst);
//	
//	//Threshold operation
//	/// Create a window to display results
//	//namedWindow(window_name, CV_WINDOW_AUTOSIZE);
//	/// Create Trackbar to choose type of Threshold
//	//////////createTrackbar(trackbar_type,
//	//////////	window_name, &threshold_type,
//	//////////	max_type, Threshold_Demo);
//	//////////createTrackbar(trackbar_value,
//	//////////	window_name, &threshold_value,
//	//////////	max_value, Threshold_Demo);
//	///////////// Call the function to initialize
//	//////////Threshold_Demo(0, 0);
//	///////////// Wait until user finishes program
//	//////////while (true)
//	//////////{
//	//////////	int c;
//	//////////	c = waitKey(20);
//	//////////	if ((char)c == 27)
//	//////////	{
//	//////////		break;
//	//////////	}
//	//////////}
//
//	waitKey(0); //wait infinite time for a keypress
//
//	//destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"
//
//	return 0;
//}

//void Threshold_Demo(int, void*)
//{
//	/* 0: Binary
//	1: Binary Inverted
//	2: Threshold Truncated
//	3: Threshold to Zero
//	4: Threshold to Zero Inverted
//	*/
//
//	threshold(gray, tDst, threshold_value, max_BINARY_value, threshold_type);
//
//	//imshow(window_name, tDst);
//}


