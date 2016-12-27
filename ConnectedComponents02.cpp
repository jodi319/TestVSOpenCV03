#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

//![variables]
Mat src, src_gray;
Mat dst, detected_edges;

int main(int argc, const char** argv)
{
		ofstream myConnectedComponents02file;
		myConnectedComponents02file.open("myConnectedComponents02file.txt");

		src = imread("connectedComponentImage03.jpg"); //read the image data in the file "MyPic.JPG" and store it in 'img'
		imshow("oRIGINAL iMAGE", src);
		myConnectedComponents02file << "SRC Image Size= " << src.size() << "\n";
		myConnectedComponents02file << "SRC Image Type= " << src.type() << "\n";
		myConnectedComponents02file << "\n";

		Mat im_gray;
		cvtColor(src, im_gray, CV_RGB2GRAY);

		Mat img_bw = im_gray > 128;

		int threshval = 100;
		cv::cvtColor(src, im_gray, cv::COLOR_BGR2GRAY);
		// Threshold it so it becomes binary
		cv::Mat binaryImg = threshval < 128 ? (im_gray < threshval) : (im_gray > threshval);
		cv::Mat labelImage;
		int nLabels = cv::connectedComponents(binaryImg, labelImage, 8);
		//imshow("labelImage", labelImage);

		//so your image is quite dark. Just for visualization purposes
		//that will scale the values to a visible range.
		Mat seeMyLabels;
		normalize(labelImage, seeMyLabels, 0, 255, NORM_MINMAX, CV_8U);
		imshow("Labels", seeMyLabels);

		Mat Labels, Stats, labelStatsImage;
		int mLabels = cv::connectedComponentsWithStats(binaryImg, labelStatsImage, Labels, Stats,8);
		//imshow("labelStatsImage", labelStatsImage);
		Mat seeMyStatsLabels;
		normalize(labelStatsImage, seeMyStatsLabels, 0, 255, NORM_MINMAX, CV_8U);
		imshow("StatsLabels", seeMyStatsLabels);
		myConnectedComponents02file << "connectedComponentsWithStats Image Size= " << mLabels << "\n";
		myConnectedComponents02file << "connectedComponentsWithStats Labels Size (w,h)= " << Labels.size().width << ", " << Labels.size().height<< "\n";
		myConnectedComponents02file << "connectedComponentsWithStats Labels= " << Labels << "\n";
		myConnectedComponents02file << "\n";
		myConnectedComponents02file << "connectedComponentsWithStats Stats Size(w,h)= " << Stats.size().width << ", " << Stats.size().height << "\n";
		myConnectedComponents02file << "connectedComponentsWithStats Stats= " << Stats << "\n";
		myConnectedComponents02file << "\n";

		myConnectedComponents02file.close();
		waitKey(0);
		return 0;
}