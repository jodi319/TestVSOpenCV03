//#include <opencv2/core/utility.hpp>
//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//#include <iostream>
//#include <fstream>
//
//using namespace cv;
//using namespace std;
//
////![variables]
//Mat src, src_gray;
//Mat dst, detected_edges;
//
//int main(int argc, const char** argv)
//{
//		ofstream myConnectedComponents02file;
//		myConnectedComponents02file.open("myConnectedComponents02file.txt");
//
//		src = imread("connectedComponentImage04.jpg"); //read the image data in the file "MyPic.JPG" and store it in 'img'
//		imshow("oRIGINAL iMAGE", src);
//		myConnectedComponents02file << "SRC Image Size= " << src.size() << "\n";
//		myConnectedComponents02file << "SRC Image Type= " << src.type() << "\n";
//		myConnectedComponents02file << "\n";
//
//		Mat im_gray;
//		cvtColor(src, im_gray, CV_RGB2GRAY);
//
//		Mat img_bw = im_gray > 128;
//
//		int threshval = 100;
//		cv::cvtColor(src, im_gray, cv::COLOR_BGR2GRAY);
//		// Threshold it so it becomes binary
//		cv::Mat binaryImg = threshval < 128 ? (im_gray < threshval) : (im_gray > threshval);
//		cv::Mat labelImage;
//		int nLabels = cv::connectedComponents(binaryImg, labelImage, 8);
//		//imshow("labelImage", labelImage);
//
//		//so your image is quite dark. Just for visualization purposes
//		//that will scale the values to a visible range.
//		Mat seeMyLabels;
//		normalize(labelImage, seeMyLabels, 0, 255, NORM_MINMAX, CV_8U);
//		imshow("Labels", seeMyLabels);
//
//		Mat Centroids, Stats, labelStatsImage;
//		int mLabels = cv::connectedComponentsWithStats(binaryImg, labelStatsImage, Stats, Centroids,8);
//		//imshow("labelStatsImage", labelStatsImage);
//		Mat seeMyStatsLabels;
//		normalize(labelStatsImage, seeMyStatsLabels, 0, 255, NORM_MINMAX, CV_8U);
//		myConnectedComponents02file << "Number of connected components = " << nLabels << std::endl << std::endl;
//
//		for (int label = 1; label < mLabels; ++label) {
//			myConnectedComponents02file << "Component " << label << std::endl;
//			myConnectedComponents02file << "CC_STAT_LEFT   = " << Stats.at<int>(label, cv::CC_STAT_LEFT) << std::endl;
//			myConnectedComponents02file << "CC_STAT_TOP    = " << Stats.at<int>(label, cv::CC_STAT_TOP) << std::endl;
//			myConnectedComponents02file << "CC_STAT_WIDTH  = " << Stats.at<int>(label, cv::CC_STAT_WIDTH) << std::endl;
//			myConnectedComponents02file << "CC_STAT_HEIGHT = " << Stats.at<int>(label, cv::CC_STAT_HEIGHT) << std::endl;
//			myConnectedComponents02file << "CC_STAT_AREA   = " << Stats.at<int>(label, cv::CC_STAT_AREA) << std::endl;
//			myConnectedComponents02file << "CENTER   = (" << Centroids.at<double>(label, 0) << "," << Centroids.at<double>(label, 1) << ")" << std::endl << std::endl;
//		}
//		myConnectedComponents02file << "\n";
//		myConnectedComponents02file << "\n";
//		imshow("StatsLabels", seeMyStatsLabels);
//		myConnectedComponents02file << "connectedComponentsWithStats Image Size= " << mLabels << "\n";
//		myConnectedComponents02file << "connectedComponentsWithStats Labels Size (w,h)= " << Centroids.size().width << ", " << Centroids.size().height<< "\n";
//		myConnectedComponents02file << "connectedComponentsWithStats Labels= " << Centroids << "\n";
//		myConnectedComponents02file << "\n";
//		myConnectedComponents02file << "connectedComponentsWithStats Stats Size(w,h)= " << Stats.size().width << ", " << Stats.size().height << "\n";
//		myConnectedComponents02file << "connectedComponentsWithStats Stats= " << Stats << "\n";
//		myConnectedComponents02file << "\n";
//
//		myConnectedComponents02file.close();
//		waitKey(0);
//		return 0;
//}