///**
//* @file CannyDetector_Demo.cpp
//* @brief Sample code showing how to detect edges using the Canny Detector
//* @author OpenCV team
//*/
//
//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//#include <iostream>
//#include <fstream>
//using namespace cv;
//using namespace std;
//
////![variables]
//Mat src, src_gray;
//Mat dst, detected_edges;
//
//int edgeThresh = 1;
//int lowThreshold;
//int const max_lowThreshold = 100;
//int ratio = 3;
//int kernel_size = 3;
//const char* window_name = "Edge Map";
//int ddepth = CV_32FC1;// CV_16S;
//int scale = 1;
//int delta = 0;
///// Generate grad_x and grad_y
//Mat grad_x, grad_y;
//Mat abs_grad_x, abs_grad_y;
////------------------Angle Histogram Parameters--------
//int binSize = 5;
//int AngleLimit = 360;
///// Establish the number of bins
//int histSize = AngleLimit/ binSize;
///// Set the ranges ( for B,G,R) )
//float rangeA[] = { 0, 360 };
//const float* histRange = { rangeA };
//Mat angle_hist;
//bool uniform = true;
//bool myAccumulate = false;
//int channels[1];
//
//int threshold_value = 0;
//int threshold_type = 0;;
//int const max_value = 255;
//int const max_type = 4;
//int const max_BINARY_value = 255;
//char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
//char* trackbar_value = "Value";
//Mat binaryImage;
//char* binary_window_name = "Binary";
///// Function headers
//void Binary_Demo(int, void*);
//
////Brightness and Contrast Correction
//Mat BrightContrastImage;
//float clipHistPercent = 0;
////void BrightnessAndContrastAuto(const cv::Mat &src, cv::Mat dst);
//
////Equalized Image
//Mat equalizedImg;
////----------------------------------------------------
////![variables]
//string type2str(int type) {
//	string r;
//
//	uchar depth = type & CV_MAT_DEPTH_MASK;
//	uchar chans = 1 + (type >> CV_CN_SHIFT);
//
//	switch (depth) {
//	case CV_8U:  r = "8U"; break;
//	case CV_8S:  r = "8S"; break;
//	case CV_16U: r = "16U"; break;
//	case CV_16S: r = "16S"; break;
//	case CV_32S: r = "32S"; break;
//	case CV_32F: r = "32F"; break;
//	case CV_64F: r = "64F"; break;
//	default:     r = "User"; break;
//	}
//
//	r += "C";
//	r += (chans + '0');
//
//	return r;
//}
//
//// Computes the 1D histogram.
//cv::MatND getHistogram(const cv::Mat &data) {
//	cv::MatND hist;
//
//	ofstream myHistogramFile2;
//	myHistogramFile2.open("myHistogramFile2.txt");
//
//	// Compute histogram
//	//calcHist(&data, 1, 0, Mat(), angle_hist, 1, &histSize, &histRange, uniform, myAccumulate);
//	calcHist(&data,
//		1, // histogram from 1 image only
//		channels, // the channel used
//		cv::Mat(), // no mask is used
//		hist, // the resulting histogram
//		1, // it is a 1D histogram
//		&histSize, // number of bins
//		&histRange, // pixel value range
//		uniform,
//		myAccumulate
//	);
//
//
//	// Plot the histogram
//	int hist_w = 512; int hist_h = 400;   myHistogramFile2 << "hist_w= " << hist_w << "\n";    myHistogramFile2 << "hist_h= " << hist_h << "\n";
//	int bin_w = cvRound((double)hist_w / histSize);   myHistogramFile2 << "bin_w= " << bin_w << "\n";
//
//	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));   myHistogramFile2 << "Black Image of size(h,w)= (" << hist_h << "," << hist_w <<")"<< "\n";
//	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
//	
//	myHistogramFile2 << "histSize= " << histSize << "\n";
//	myHistogramFile2 << "\n";    myHistogramFile2 << "\n";
//	myHistogramFile2 << "Line(" << 71 << ")= (" << bin_w*(70) << "," << hist_h - cvRound(hist.at<float>(70)) << ") TO (" << bin_w*(71) << "," << hist_h - cvRound(hist.at<float>(71)) << ")" << "\n";
//	for (int i = 1; i < histSize; i++)
//	{
//		
//		myHistogramFile2 << "histSize(" << i-1 << ")= " << hist.at<float>(i)<<"   ------   ";
//		myHistogramFile2 << "Line(" << i-1<< ")= ("<< bin_w*(i - 1) << "," << hist_h - cvRound(hist.at<float>(i - 1)) << ") TO (" << bin_w*(i) <<"," << hist_h - cvRound(hist.at<float>(i)) << ")" << "\n";
//
//		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
//			Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
//			Scalar(255, 0, 0), 2, 8, 0);
//	}
//
//	//namedWindow("Result", 1);    imshow("Result", histImage);
//	myHistogramFile2.close();
//	//waitKey(0);
//	return histImage;
//}
//
//// Computes the 1D histogram and returns an image of it.
//cv::Mat getHistogramImage(const cv::Mat &image) {
//	channels[0] = 0;
//	// Compute histogram first
//	cv::MatND hist = getHistogram(image);
//	// Get min and max bin values
//	double maxVal = 0;
//	double minVal = 0;
//	cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
//	// Image on which to display histogram
//	cv::Mat histImg(histSize, histSize,
//		CV_8U, cv::Scalar(255));
//	// set highest point at 90% of nbins
//	int hpt = static_cast<int>(0.9*histSize);
//	// Draw a vertical line for each bin
//	for (int h = 0; h < histSize; h++) {
//		float binVal = hist.at<float>(h);
//		int intensity = static_cast<int>(binVal*hpt / maxVal);
//		// This function draws a line between 2 points
//		cv::line(histImg, cv::Point(h, histSize),
//			cv::Point(h, histSize - intensity),
//			cv::Scalar::all(0));
//	}
//	return histImg;
//}
///**
//* @function CannyThreshold
//* @brief Trackbar callback - Canny thresholds input with a ratio 1:3
//*/
//static void CannyThreshold(const cv::Mat &data)
//{
//
//	//![reduce_noise]
//	//Reduce noise with a kernel 3x3
//	blur(src_gray, detected_edges, Size(3, 3));
//	//![reduce_noise]
//	//cout << "src_gray = " << (double)src_gray.at<uchar>(2, 23) << "\n";
//	imshow("Blurred Image", detected_edges);
//	//![canny]
//	//Canny detector
//	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
//	//![canny]
//	imshow("Canny Image", detected_edges);
//	//-----------------------------------------------------------------------------------
//	//int ddepth = CV_32FC1;// CV_16S;
//	//int scale = 1;
//	//int delta = 0;
//	///// Generate grad_x and grad_y
//	//Mat grad_x, grad_y;
//	//Mat abs_grad_x, abs_grad_y;
//
//	/// Gradient X
//	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
//	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
//
//	/// Gradient Y
//	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
//	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
//	//![sobel]
//
//	cv::Mat angle(src.size(), CV_64F);
//
//	//Mat dx(src_gray.rows, src_gray.cols, CV_16SC1);
//	//Mat dy(src_gray.rows, src_gray.cols, CV_16SC1);
//	Mat Mag(src_gray.size(), CV_32FC1);
//	Mat Angle(src_gray.size(), CV_32FC1);
//
//	////----------------------------------------------------
//	//ofstream myDYfile;
//	//myDYfile.open("dataDY.txt");
//	//myDYfile << grad_y;
//	//myDYfile.close();
//	////----------------------------------------------------
//	////cout << "Angle = " << Angle << "\n";
//	////----------------------------------------------------
//	//ofstream myDXfile;
//	//myDXfile.open("dataDX.txt");
//	//myDXfile << grad_x;
//	//myDXfile.close();
//	////----------------------------------------------------
//
//	double minM, maxM, minA, maxA;
//	
//
//	cartToPolar(grad_x, grad_y, Mag, Angle, true);
//	cv::minMaxLoc(Mag, &minM, &maxM);
//	cv::minMaxLoc(Angle, &minA, &maxA);
//	//// know the number of channels the image has
//	//cout << "original image channels: " << Angle.channels() << "gray image channels: " << gray.channels() << endl;
//	string ty = type2str(Angle.type());
//	cout << "Matrix: \n" << ty.c_str() << " " << Angle.cols << "x" << Angle.rows << "\n";
//	////----------------------------------------------------
//	ofstream myAngleFile;
//	myAngleFile.open("myAngle.csv");
//	//myAnglefile << Angle;
//	myAngleFile << "Original Image size= " << src.size() << "\n";
//	myAngleFile << "Angle size= " << Angle.size() << "\n";
//	myAngleFile << "\n";
//	////----------------------------------------------------
//
//	/// Compute the histograms:
//	MatND myHist = getHistogram(Angle);
//	//calcHist(&Angle, 1, 0, Mat(), angle_hist, 1, &histSize, &histRange, uniform, myAccumulate);
//	ofstream myHistogramFile;
//	myHistogramFile.open("myHistogramFile.csv", ios::app);
//	//myHistogramFile << "Original Image size= " << src.size() << "\n";
//	//myHistogramFile << "Angle size= "<< Angle.size() << "\n";
//	//myHistogramFile << "number of bins= " << histSize << "\n";
//	//myHistogramFile << "pixel value range= " << histRange << "\n";
//	myHistogramFile << "\n";
//	myAngleFile << myHist;
//	for (size_t i = 0; i < Angle.rows; i++)
//	{
//		//myHistogramFile << i << "\n";
//		const float* Row_i = Angle.ptr<float>(i);
//		//cout << "i" << i << "\n";
//		for (size_t j = 0; j < Angle.cols; j++)
//		{
//			//myHistogramFile << j << " -- ";
//			/// Establish the number of bins
//			int histSize = 256;
//
//
//			////cout << "j" << j << "\n";
//			////cout << "(i,j) - Mi[j] = (" << i << ", " << j << ")" << Mi[j] << "\n";
//
//			//////----------------------------------------------------
//			//ofstream myAngleIJfile;
//			//myAngleIJfile.open("myAngleIJ.txt", ios::app);
//			//myHistogramFile << "(i,j) = " << i << "," << j << " -- " << Row_i[j] << "\n";
//			myHistogramFile << Row_i[j] << "\n";
//			//myAngleIJfile.close();
//			//////----------------------------------------------------
//			////if ((angle.at<uchar>(j,i) > 180) && (angle.at<uchar>(j,i) < 270))
//			////{
//			////	cout << "180 > angle < 270 = " << (int)angle.at<uchar>(i, j) << "\n";
//			////}
//		}
//	}
//	myHistogramFile.close();
//	cout << "Angle size = " << Angle.size() << "\n";
//	cout << "Maximum Magnitude = " << maxM << "\n";
//	cout << "Minimum Magnitude = " << minM << "\n";
//	cout << "Maximum Angle = " << maxA << "\n";
//	cout << "Minimum Angle = " << minA << "\n";
//	//imshow("Magnitude", Mag);
//	//imshow("Angle", Angle);
//	////----------------------------------------------------
//	//ofstream myMagfile;
//	//myMagfile.open("dataMag.txt");
//	//myMagfile << Mag;
//	//myMagfile.close();
//	////----------------------------------------------------
//	////----------------------------------------------------
//	//ofstream myAnglefile;
//	//myAnglefile.open("dataAngle.txt");
//	//myAnglefile << Angle;
//	//myAnglefile.close();
//	////----------------------------------------------------
//
//	// Using Canny's output as a mask, we display our result
//	//![fill]
//	dst = Scalar::all(0);
//	//![fill]
//
//	//![copyto]
//	src.copyTo(dst, detected_edges);
//	//![copyto]
//
//	//![display]
//	//namedWindow("Original Image", WINDOW_AUTOSIZE);
//	//imshow("Original Image", src);
//
//	//imshow(window_name, dst);
//	//![display]
//}
//
/////**
////*  \brief Automatic brightness and contrast optimization with optional histogram clipping
////*  \param [in]src Input image GRAY or BGR or BGRA
////*  \param [out]dst Destination image
////*  \param clipHistPercent cut wings of histogram at given percent tipical=>1, 0=>Disabled
////*  \note In case of BGRA image, we won't touch the transparency
////*/
////void BrightnessAndContrastAuto(const cv::Mat &src3, cv::Mat dst3)
////{
////
////	CV_Assert(clipHistPercent >= 0);
////	CV_Assert((src3.type() == CV_8UC1) || (src3.type() == CV_8UC3) || (src3.type() == CV_8UC4));
////
////	int histSize = 256;
////	float alpha, beta;
////	double minGray = 0, maxGray = 0;
////
////	//to calculate grayscale histogram
////	cv::Mat gray3;
////	if (src3.type() == CV_8UC1) gray3 = src3;
////	else if (src3.type() == CV_8UC3) cvtColor(src3, gray3, CV_BGR2GRAY);
////	else if (src3.type() == CV_8UC4) cvtColor(src3, gray3, CV_BGRA2GRAY);
////	if (clipHistPercent == 0)
////	{
////		// keep full available range
////		cv::minMaxLoc(gray3, &minGray, &maxGray);
////	}
////	else
////	{
////		cv::Mat hist; //the grayscale histogram
////
////		float range[] = { 0, 256 };
////		const float* histRange = { range };
////		bool uniform = true;
////		bool accumulate = false;
////		calcHist(&gray3, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);
////
////		// calculate cumulative distribution from the histogram
////		std::vector<float> accumulator(histSize);
////		accumulator[0] = hist.at<float>(0);
////		for (int i = 1; i < histSize; i++)
////		{
////			accumulator[i] = accumulator[i - 1] + hist.at<float>(i);
////		}
////
////		// locate points that cuts at required value
////		float max = accumulator.back();
////		clipHistPercent *= (max / 100.0); //make percent as absolute
////		clipHistPercent /= 2.0; // left and right wings
////								// locate left cut
////		minGray = 0;
////		while (accumulator[minGray] < clipHistPercent)
////			minGray++;
////
////		// locate right cut
////		maxGray = histSize - 1;
////		while (accumulator[maxGray] >= (max - clipHistPercent))
////			maxGray--;
////	}
////
////	// current range
////	float inputRange = maxGray - minGray;
////
////	alpha = (histSize - 1) / inputRange;   // alpha expands current range to histsize range
////	beta = -minGray * alpha;             // beta shifts current range so that minGray will go to 0
////
////										 // Apply brightness and contrast normalization
////										 // convertTo operates with saurate_cast
////	src3.convertTo(dst, -1, alpha, beta);
////
////	// restore alpha channel from source 
////	if (dst3.type() == CV_8UC4)
////	{
////		int from_to[] = { 3, 3 };
////		cv::mixChannels(&src3, 4, &dst3, 1, from_to, 1);
////	}
////	BrightContrastImage = dst3;
////	imshow("BrightContrastImage", dst3);
////	return;
////}
//
///**
//* @function main
//*/
////int main(int, char** argv)
//int main(int argc, const char** argv)
//{
//	//![load]
//	//src = imread(argv[1], IMREAD_COLOR); // Load an image
//	src = imread("20161215 02.33_368L.jpg", CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "MyPic.JPG" and store it in 'img'
//	imshow("oRIGINAL iMAGE", src);
//
//	if (src.empty())
//	{
//		return -1;
//	}
//	//![load]
//
//	//![create_mat]
//	/// Create a matrix of the same type and size as src (for dst)
//	dst.create(src.size(), src.type());
//	//![create_mat]
//
//	//![convert_to_gray]
//	cvtColor(src, src_gray, COLOR_BGR2GRAY);
//	//![convert_to_gray]
//	imshow("GrayScale Image", src_gray);
//
//	CannyThreshold(src_gray);
//
//	//Mat tempImage = src;
//	//BrightnessAndContrastAuto(src, tempImage);
//	Mat img = src_gray;
//
//	equalizeHist(img, equalizedImg);
//	//imshow("Equalized Image", equalizedImg);
//	//MatND myEqualHist = getHistogram(equalizedImg);
//	//imshow("Histogram of Equalized IMage", myEqualHist);
//	//----------- HISTOGRAM OF ORIGINAL IMAGE ----------------------------------------------
//	/// Compute the histograms:
//	//MatND myHistOrig = getHistogram(src_gray);
//	//imshow("Histogram of Original", myHistOrig);
//
//
//
//
//
//	//---------------------------------------------------------------------------------------
//	//----------- HISTOGRAM OF EQUALIZED IMAGE ----------------------------------------------
//	/// Compute the histograms:
//	//MatND myHistOrig = getHistogram(src_gray);
//	//imshow("Histogram of Original", myHistOrig);
//
//
//
//
//
//	//----------------------------------------------------------------------------------------
//	//----------- BINARY ----------------------------------------------
//	///// Create a window to display results
//	//namedWindow(binary_window_name, CV_WINDOW_AUTOSIZE);
//	///// Create Trackbar to choose type of Threshold
//	//createTrackbar(trackbar_value,
//	//	binary_window_name, &threshold_value,
//	//	max_value, Binary_Demo);
//	//
//	///// Call the function to initialize
//	//Binary_Demo(0, 0);
//
//	///// Wait until user finishes program
//	//while (true)
//	//{
//	//	int c;
//	//	c = waitKey(20);
//	//	if ((char)c == 27)
//	//	{
//	//		break;
//	//	}
//	//}
//
//}
//
//
///**
//* @function Binary_Demo
//*/
//void Binary_Demo(int, void*)
//{
//	threshold(src_gray, binaryImage, threshold_value, max_BINARY_value, threshold_type);
//
//	imshow(binary_window_name, binaryImage);
//	/// Wait until user exit program by pressing a key
//	waitKey(0);
//}
////--------------------------------------------------------------------------------------