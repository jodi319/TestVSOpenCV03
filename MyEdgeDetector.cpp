#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

//![variables]
Mat src, src_gray;
Mat dst, detected_edges, angleHist;
int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
const char* window_name = "Edge Map";
int ddepth = CV_32FC1;// CV_16S;
int scale = 1;
int delta = 0;
/// Generate grad_x and grad_y
Mat grad_x, grad_y;
Mat abs_grad_x, abs_grad_y;
//------------------Angle Histogram Parameters--------
int binSize = 9;
int AngleLimit = 360;
/// Establish the number of bins
int histSize = AngleLimit / binSize;
/// Set the ranges ( for B,G,R) )
float rangeA[] = { 0, 360 };
const float* histRange = { rangeA };
Mat angle_hist;
bool uniform = true;
bool myAccumulate = false;
int channels[1];
//![variables]

// Computes the 1D histogram.
cv::MatND getHistogram(const cv::Mat &data) {
	cv::MatND hist;

	ofstream myAngleHistFile;
	myAngleHistFile.open("myAngleHistFile.txt");

	// Compute histogram
	//calcHist(&data, 1, 0, Mat(), angle_hist, 1, &histSize, &histRange, uniform, myAccumulate);
	calcHist(&data,
		1, // histogram from 1 image only
		channels, // the channel used
		cv::Mat(), // no mask is used
		hist, // the resulting histogram
		1, // it is a 1D histogram
		&histSize, // number of bins
		&histRange, // pixel value range
		uniform,
		myAccumulate
	);


	// Plot the histogram
	int hist_w = 512; int hist_h = 400;   myAngleHistFile << "hist_w= " << hist_w << "\n";    myAngleHistFile << "hist_h= " << hist_h << "\n";
	int bin_w = cvRound((double)hist_w / histSize);   myAngleHistFile << "bin_w= " << bin_w << "\n";

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));   myAngleHistFile << "Black Image of size(h,w)= (" << hist_h << "," << hist_w << ")" << "\n";
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	myAngleHistFile << "AngleLimit= " << AngleLimit << "\n";
	myAngleHistFile << "binSize= " << binSize << "\n";
	myAngleHistFile << "(number of bins) histSize= " << histSize << "\n";
	myAngleHistFile << "\n";    myAngleHistFile << "\n";
	myAngleHistFile << "Line(" << 71 << ")= (" << bin_w*(70) << "," << hist_h - cvRound(hist.at<float>(70)) << ") TO (" << bin_w*(71) << "," << hist_h - cvRound(hist.at<float>(71)) << ")" << "\n";
	for (int i = 1; i < histSize; i++)
	{

		myAngleHistFile << "histSize(" << i - 1 << ")= " << hist.at<float>(i) << "   ------   ";
		myAngleHistFile << "Line(" << i - 1 << ")= (" << bin_w*(i - 1) << "," << hist_h - cvRound(hist.at<float>(i - 1)) << ") TO (" << bin_w*(i) << "," << hist_h - cvRound(hist.at<float>(i)) << ")" << "\n";

		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}

	namedWindow("Result", 1);    imshow("Result", histImage);
	myAngleHistFile.close();
	//waitKey(0);
	return histImage;
}

int main()
{
	ofstream myEdgeDetectorFile;
	myEdgeDetectorFile.open("myEdgeDetectorFile.txt");

	//![load]
	//src = imread(argv[1], IMREAD_COLOR); // Load an image
	src = imread("20161215 02.33_368L.jpg", CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "MyPic.JPG" and store it in 'img'
	imshow("oRIGINAL iMAGE", src);

	if (src.empty())
	{
		return -1;
	}
	//![load]

	//![convert_to_gray]
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	//![convert_to_gray]
	imshow("GrayScale Image", src_gray);

	//![reduce_noise]
	//Reduce noise with a kernel 3x3
	blur(src_gray, detected_edges, Size(3, 3));
	//![reduce_noise]
	//cout << "src_gray = " << (double)src_gray.at<uchar>(2, 23) << "\n";
	imshow("Blurred Image", detected_edges);
	//![canny]

	//Canny detector
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
	//![canny]
	imshow("Canny Image", detected_edges);

	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);

	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	//![sobel]

	//cv::Mat angle(src.size(), CV_64F);

	Mat Mag(src_gray.size(), CV_32FC1);
	Mat Angle(src_gray.size(), CV_32FC1);

	double minM, maxM, minA, maxA;


	cartToPolar(grad_x, grad_y, Mag, Angle, true);

	angleHist = getHistogram(Angle);
	//cv::minMaxLoc(Mag, &minM, &maxM);
	//cv::minMaxLoc(Angle, &minA, &maxA);

	myEdgeDetectorFile << "Original Image size= " << src.size() << "\n";
	myEdgeDetectorFile << "Angle size= " << Angle.size() << "\n";
	myEdgeDetectorFile << "\n";

	for (size_t i = 0; i < Angle.rows; i++)
	{
		//myHistogramFile << i << "\n";
		const float* Row_i = Angle.ptr<float>(i);
		//cout << "i" << i << "\n";
		for (size_t j = 0; j < Angle.cols; j++)
		{
			/// Establish the number of bins
			int histSize = 256;
			myEdgeDetectorFile << "(i,j)= (" << i << ", " << j << ")= " << Row_i[j] << "\n";
			//myEdgeDetectorFile << Row_i[j] << "\n";
		}
	}

	myEdgeDetectorFile.close();

	waitKey(0);
	return 0;
}