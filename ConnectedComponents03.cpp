//#include <iostream>
//#include <opencv2/core/utility.hpp>
//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//#include <opencv2/opencv.hpp>
//#include <math.h>
//#include <fstream>
//
//using namespace cv;
//using namespace std;
//
//const std::string keys =
//"{help      |             | print this message    }"
//"{@image    |contours     | load image            }"
//"{j         |j.png        | j image        }"
//"{contours  |contours.png | contours image        }"
//;
//
//int threshval = 60;
//int bw_constant = 128;
//
//int main(int argc, char *argv[])
//{
//	ofstream myConnectedComponents03file;
//	myConnectedComponents03file.open("myConnectedComponents03file.txt");
//
//	cv::CommandLineParser parser(argc, argv, keys);
//	parser.about("");
//	if (parser.has("help")) {
//		parser.printMessage();
//		return 0;
//	}
//
//	cv::Mat srcImg;
//	std::string file = parser.get<std::string>(0);
//	if (file == "j") {
//		file = parser.get<std::string>("j");
//	}
//	else if (file == "contours") {
//		file = parser.get<std::string>("contours");
//	}
//	srcImg = cv::imread("20161215 02.33_368L.jpg", CV_LOAD_IMAGE_UNCHANGED);
//	if (srcImg.empty()) {
//		return -1;
//	}
//
//	cv::Mat grayImg;
//	cv::cvtColor(srcImg, grayImg, cv::COLOR_BGR2GRAY);
//
//	cv::Mat binaryImg = threshval < 128 ? (grayImg < threshval) : (grayImg > threshval);
//	cv::Mat labelImage;
//	cv::Mat stats, centroids;
//	//    int nLabels = cv::connectedComponents(bw, labelImage, 8);
//	int nLabels = cv::connectedComponentsWithStats(binaryImg, labelImage, stats, centroids, 8, CV_32S);
//	std::vector<cv::Vec3b> colors(nLabels);
//	colors[0] = cv::Vec3b(0, 0, 0);
//	myConnectedComponents03file << "Number of connected components = " << nLabels << std::endl << std::endl;
//
//	for (int label = 1; label < nLabels; ++label) {
//		colors[label] = cv::Vec3b((std::rand() & 255), (std::rand() & 255), (std::rand() & 255));
//		myConnectedComponents03file << "Component " << label << std::endl;
//		myConnectedComponents03file << "CC_STAT_LEFT   = " << stats.at<int>(label, cv::CC_STAT_LEFT) << std::endl;
//		myConnectedComponents03file << "CC_STAT_TOP    = " << stats.at<int>(label, cv::CC_STAT_TOP) << std::endl;
//		myConnectedComponents03file << "CC_STAT_WIDTH  = " << stats.at<int>(label, cv::CC_STAT_WIDTH) << std::endl;
//		myConnectedComponents03file << "CC_STAT_HEIGHT = " << stats.at<int>(label, cv::CC_STAT_HEIGHT) << std::endl;
//		myConnectedComponents03file << "CC_STAT_AREA   = " << stats.at<int>(label, cv::CC_STAT_AREA) << std::endl;
//		myConnectedComponents03file << "CENTER   = (" << centroids.at<double>(label, 0) << "," << centroids.at<double>(label, 1) << ")" << std::endl << std::endl;
//	}
//	cv::Mat dst(grayImg.size(), CV_8UC3);
//	for (int r = 0; r < dst.rows; ++r) {
//		for (int c = 0; c < dst.cols; ++c) {
//			int label = labelImage.at<int>(r, c);
//			cv::Vec3b &pixel = dst.at<cv::Vec3b>(r, c);
//			pixel = colors[label];
//		}
//	}
//
//	cv::imshow("Source", srcImg);
//	cv::imshow("B&W - %f" + threshval , binaryImg);
//	cv::imshow("Connected Components", dst);
//
//	myConnectedComponents03file.close();
//
//	waitKey(0);
//
//
//	return 0;
//}