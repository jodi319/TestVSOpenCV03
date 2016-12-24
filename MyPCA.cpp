//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <stdlib.h>
//#include "windows.h" 
//#include <fstream>
//using namespace std;
//using namespace cv;
//// Function declarations
//void drawAxis(Mat&, Point, Point, Scalar, const float);
//double getOrientation(const vector<Point> &, Mat&);
//void drawAxis(Mat& img, Point p, Point q, Scalar colour, const float scale = 0.2)
//{
//	double angle;
//	double hypotenuse;
//	angle = atan2((double)p.y - q.y, (double)p.x - q.x); // angle in radians
//	hypotenuse = sqrt((double)(p.y - q.y) * (p.y - q.y) + (p.x - q.x) * (p.x - q.x));
//	//    double degrees = angle * 180 / CV_PI; // convert radians to degrees (0-180 range)
//	//    cout << "Degrees: " << abs(degrees - 180) << endl; // angle in 0-360 degrees range
//	// Here we lengthen the arrow by a factor of scale
//	q.x = (int)(p.x - scale * hypotenuse * cos(angle));
//	q.y = (int)(p.y - scale * hypotenuse * sin(angle));
//	line(img, p, q, colour, 1, CV_AA);
//	// create the arrow hooks
//	p.x = (int)(q.x + 9 * cos(angle + CV_PI / 4));
//	p.y = (int)(q.y + 9 * sin(angle + CV_PI / 4));
//	line(img, p, q, colour, 1, CV_AA);
//	p.x = (int)(q.x + 9 * cos(angle - CV_PI / 4));
//	p.y = (int)(q.y + 9 * sin(angle - CV_PI / 4));
//	line(img, p, q, colour, 1, CV_AA);
//}
//double getOrientation(const vector<Point> &pts, Mat &img)
//{
//	//Construct a buffer used by the pca analysis
//	int sz = static_cast<int>(pts.size());
//	Mat data_pts = Mat(sz, 2, CV_64FC1);	//because we cannot pass an array of 2D points, 
//	for (int i = 0; i < data_pts.rows; ++i) //but we have to arrange them in a matrix with size 
//	{										//n x 2 where n is the number of data points we have
//		data_pts.at<double>(i, 0) = pts[i].x;
//		data_pts.at<double>(i, 1) = pts[i].y;
//	}
//
///* Perform PCA analysis
//We construct a PCA object in line 12 which automatically runs PCA on the input
//data given as the first argument (data_pts). The second argument is the centre of the data set,
//but since we do not know it we pass an empty matrix Mat(), meaning that it will be estimated. 
//The final argument indicates how the data is supplied – in our case it is CV_PCA_DATA_AS_ROW 
//because each point is a row in the input matrix (data_pts).
//*/
//	PCA pca_analysis(data_pts, Mat(), CV_PCA_DATA_AS_ROW);
//	//Store the center of the object
//	//The calculated mean is stored in the "cntr" variable
//	Point cntr = Point(static_cast<int>(pca_analysis.mean.at<double>(0, 0)),
//		static_cast<int>(pca_analysis.mean.at<double>(0, 1)));
//	//Store the eigenvalues and eigenvectors
//	vector<Point2d> eigen_vecs(2);
//	vector<double> eigen_val(2);
//	for (int i = 0; i < 2; ++i)
//	{
//		/*cout << "i = " << i << "\n";
//		cout << "pca_analysis.eigenvectors.at<double>(i, 0) = " << pca_analysis.eigenvectors.at<double>(i, 0) << "\n";
//		cout << "pca_analysis.eigenvectors.at<double>(i, 1) = " << pca_analysis.eigenvectors.at<double>(i, 1) << "\n";
//		cout << "Point2d(pca_analysis.eigenvectors.at<double>(i, 0),pca_analysis.eigenvectors.at<double>(i, 1)) = " << Point2d(pca_analysis.eigenvectors.at<double>(i, 0),pca_analysis.eigenvectors.at<double>(i, 1)) << "\n";
//		cout << "eigen_vecs[i] = " << eigen_vecs[i] << "\n";*/
//		eigen_vecs[i] = Point2d(pca_analysis.eigenvectors.at<double>(i, 0),
//			pca_analysis.eigenvectors.at<double>(i, 1));
//		//cout << "eigen_vecs[i] = " << eigen_vecs[i] << "\n";
//		//cout << "eigen_val[i] = " << eigen_val[i] << "\n";
//		if (i==0)
//		{
//			//cout << "pca_analysis.eigenvalues.at<double>(0, i) = " << pca_analysis.eigenvalues.at<double>(0, i) << "\n";
//			eigen_val[i] = pca_analysis.eigenvalues.at<double>(0, i);
//			//cout << "eigen_val[i] = " << eigen_val[i] << "\n";
//		}
//	}
//	// Draw the principal components
//	circle(img, cntr, 3, Scalar(255, 0, 255), 2);
//	Point p1 = cntr + 0.02 * Point(static_cast<int>(eigen_vecs[0].x * eigen_val[0]), static_cast<int>(eigen_vecs[0].y * eigen_val[0]));
//	Point p2 = cntr - 0.02 * Point(static_cast<int>(eigen_vecs[1].x * eigen_val[1]), static_cast<int>(eigen_vecs[1].y * eigen_val[1]));
//	drawAxis(img, cntr, p1, Scalar(0, 255, 0), 1);
//	drawAxis(img, cntr, p2, Scalar(255, 255, 0), 5);
//	double angle = atan2(eigen_vecs[0].y, eigen_vecs[0].x); // orientation in radians
//	return angle;
//}
//int main(int, char** argv)
//{
//	int largest_area = 0;
//	int largest_contour_index = 0;
//	Rect bounding_rect;
//
//	// Load image
//	//    Mat src = imread("pca_test1.jpg");
//	Mat src = imread("20140612_MINEGARDEN_SURVEY_sds_UseRawDataSetting_01_18_30_CylindricalMine01.jpg", CV_LOAD_IMAGE_UNCHANGED);
//	// Check if image is loaded successfully
//	if (!src.data || src.empty())
//	{
//		cout << "Problem loading image!!!" << endl;
//		return EXIT_FAILURE;
//	}
//	imshow("src", src);
//	// Convert image to grayscale
//	Mat gray;
//	cvtColor(src, gray, COLOR_BGR2GRAY);
//	// Convert image to binary
//	Mat bw;
//	threshold(gray, bw, 50, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
//	// Find all the contours in the thresholded image
//	vector<Vec4i> hierarchy;
//	vector<vector<Point> > contours;
//	/* mode – Contour retrieval mode(if you use Python see also a note below).
//	CV_RETR_EXTERNAL retrieves only the extreme outer contours.
//	It sets hierarchy[i][2] = hierarchy[i][3] = -1 for all the contours.
//	CV_RETR_LIST retrieves all of the contours without establishing any hierarchical relationships.
//	CV_RETR_CCOMP retrieves all of the contours and organizes them into a two
//		- level hierarchy.At the top level, there are external boundaries of the 
//			components.At the second level, there are boundaries of the holes.
//			If there is another contour inside a hole of a connected component,
//			it is still put at the top level.
//	CV_RETR_TREE retrieves all of the contours and reconstructs a full hierarchy of nested contours.
//	This full hierarchy is built and shown in the OpenCV contours.c demo.
//		*/
//	findContours(bw, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
//	//cout << "hierarchy = " << hierarchy << "\n";
//	//--------------------------------------------------------------------------------
//	//// you could also reuse img1 here
//	Mat mask = Mat::zeros(gray.rows, gray.cols, CV_8UC1);
//	//// CV_FILLED fills the connected components found
//	//drawContours(mask, contours, -1, Scalar(255), CV_FILLED);
//	//// let's create a new image now
//	//Mat crop(src.rows, src.cols, CV_8UC3);
//	//// set background to green
//	//crop.setTo(Scalar(0, 255, 0));
//	//// and copy the magic apple
//	//src.copyTo(crop, mask);
//	//// normalize so imwrite(...)/imshow(...) shows the mask correctly!
//	//normalize(mask.clone(), mask, 0.0, 255.0, CV_MINMAX, CV_8UC1);
//	//// show the images
//	//imshow("original", src);
//	//imshow("mask", mask);
//	//imshow("canny", gray);
//	//imshow("cropped", crop);
//	//--------------------------------------------------------------------------------
//
//	//for (size_t i = 0; i < contours.size(); ++i)
//	//{
//	//	// Calculate the area of each contour
//	//	double area = contourArea(contours[i]);
//	//	// Ignore contours that are too small or too large
//	//	if (area < 1000) continue;
//	//	// Draw each contour only for visualisation purposes
//	//	cout << "Number of contours with area > 1000 = " << contours.size() << "\n";
//
//	//	drawContours(src, contours, static_cast<int>(i), Scalar(255,0,0), 1, 8, hierarchy, 0);
//	//	// Find the orientation of each shape
//	//	//getOrientation(contours[i], src);
//	//}
//
//	//double area;
//	//Find biggest contours
//	/*cout << "Total number of contours = " << contours.size() << "\n";*/
//	for (int i = 0; i< contours.size(); i++) // iterate through each contour. 
//	{
//		double a = contourArea(contours[i], false);  //  Find the area of contour
//		if (a>1000 && a<4000) {
//			//largest_area = a;
//			cout << "Area size = " << a << "\n";
//			largest_contour_index = i;                //Store the index of largest contour
//			bounding_rect = boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
//			drawContours(mask, contours, static_cast<int>(i), Scalar(255, 0, 0), 1, 8, hierarchy, 0);
//			drawContours(src, contours, static_cast<int>(i), Scalar(255, 0, 0), 1, 8, hierarchy, 0);
//		}
//
//	}
//	imshow("mask", mask);
//	imshow("output", src);
//	waitKey(0);
//	return 0;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////#include <iostream>
////#include <opencv2/opencv.hpp>
////#include <stdlib.h>
////#include "windows.h" 
////#include <fstream>
////using namespace std;
////using namespace cv;
////// Function declarations
////void drawAxis(Mat&, Point, Point, Scalar, const float);
////double getOrientation(const vector<Point> &, Mat&);
////void drawAxis(Mat& img, Point p, Point q, Scalar colour, const float scale = 0.2)
////{
////	double angle;
////	double hypotenuse;
////	angle = atan2((double)p.y - q.y, (double)p.x - q.x); // angle in radians
////	hypotenuse = sqrt((double)(p.y - q.y) * (p.y - q.y) + (p.x - q.x) * (p.x - q.x));
////	//    double degrees = angle * 180 / CV_PI; // convert radians to degrees (0-180 range)
////	//    cout << "Degrees: " << abs(degrees - 180) << endl; // angle in 0-360 degrees range
////	// Here we lengthen the arrow by a factor of scale
////	q.x = (int)(p.x - scale * hypotenuse * cos(angle));
////	q.y = (int)(p.y - scale * hypotenuse * sin(angle));
////	line(img, p, q, colour, 1, CV_AA);
////	// create the arrow hooks
////	p.x = (int)(q.x + 9 * cos(angle + CV_PI / 4));
////	p.y = (int)(q.y + 9 * sin(angle + CV_PI / 4));
////	line(img, p, q, colour, 1, CV_AA);
////	p.x = (int)(q.x + 9 * cos(angle - CV_PI / 4));
////	p.y = (int)(q.y + 9 * sin(angle - CV_PI / 4));
////	line(img, p, q, colour, 1, CV_AA);
////}
////double getOrientation(const vector<Point> &pts, Mat &img)
////{
////	//Construct a buffer used by the pca analysis
////	int sz = static_cast<int>(pts.size());
////	Mat data_pts = Mat(sz, 2, CV_64FC1);	//because we cannot pass an array of 2D points, 
////	for (int i = 0; i < data_pts.rows; ++i) //but we have to arrange them in a matrix with size 
////	{										//n x 2 where n is the number of data points we have
////		data_pts.at<double>(i, 0) = pts[i].x;
////		data_pts.at<double>(i, 1) = pts[i].y;
////	}
////
/////* Perform PCA analysis
////We construct a PCA object in line 12 which automatically runs PCA on the input
////data given as the first argument (data_pts). The second argument is the centre of the data set,
////but since we do not know it we pass an empty matrix Mat(), meaning that it will be estimated. 
////The final argument indicates how the data is supplied – in our case it is CV_PCA_DATA_AS_ROW 
////because each point is a row in the input matrix (data_pts).
////*/
////	PCA pca_analysis(data_pts, Mat(), CV_PCA_DATA_AS_ROW);
////	//Store the center of the object
////	//The calculated mean is stored in the "cntr" variable
////	Point cntr = Point(static_cast<int>(pca_analysis.mean.at<double>(0, 0)),
////		static_cast<int>(pca_analysis.mean.at<double>(0, 1)));
////	//Store the eigenvalues and eigenvectors
////	vector<Point2d> eigen_vecs(2);
////	vector<double> eigen_val(2);
////	for (int i = 0; i < 2; ++i)
////	{
////		/*cout << "i = " << i << "\n";
////		cout << "pca_analysis.eigenvectors.at<double>(i, 0) = " << pca_analysis.eigenvectors.at<double>(i, 0) << "\n";
////		cout << "pca_analysis.eigenvectors.at<double>(i, 1) = " << pca_analysis.eigenvectors.at<double>(i, 1) << "\n";
////		cout << "Point2d(pca_analysis.eigenvectors.at<double>(i, 0),pca_analysis.eigenvectors.at<double>(i, 1)) = " << Point2d(pca_analysis.eigenvectors.at<double>(i, 0),pca_analysis.eigenvectors.at<double>(i, 1)) << "\n";
////		cout << "eigen_vecs[i] = " << eigen_vecs[i] << "\n";*/
////		eigen_vecs[i] = Point2d(pca_analysis.eigenvectors.at<double>(i, 0),
////			pca_analysis.eigenvectors.at<double>(i, 1));
////		//cout << "eigen_vecs[i] = " << eigen_vecs[i] << "\n";
////		//cout << "eigen_val[i] = " << eigen_val[i] << "\n";
////		if (i==0)
////		{
////			//cout << "pca_analysis.eigenvalues.at<double>(0, i) = " << pca_analysis.eigenvalues.at<double>(0, i) << "\n";
////			eigen_val[i] = pca_analysis.eigenvalues.at<double>(0, i);
////			//cout << "eigen_val[i] = " << eigen_val[i] << "\n";
////		}
////	}
////	// Draw the principal components
////	circle(img, cntr, 3, Scalar(255, 0, 255), 2);
////	Point p1 = cntr + 0.02 * Point(static_cast<int>(eigen_vecs[0].x * eigen_val[0]), static_cast<int>(eigen_vecs[0].y * eigen_val[0]));
////	Point p2 = cntr - 0.02 * Point(static_cast<int>(eigen_vecs[1].x * eigen_val[1]), static_cast<int>(eigen_vecs[1].y * eigen_val[1]));
////	drawAxis(img, cntr, p1, Scalar(0, 255, 0), 1);
////	drawAxis(img, cntr, p2, Scalar(255, 255, 0), 5);
////	double angle = atan2(eigen_vecs[0].y, eigen_vecs[0].x); // orientation in radians
////	return angle;
////}
////int main(int, char** argv)
////{
////	int largest_area = 0;
////	int largest_contour_index = 0;
////	Rect bounding_rect;
////
////	// Load image
////	//    Mat src = imread("pca_test1.jpg");
////	Mat src = imread("20140612_MINEGARDEN_SURVEY_sds_UseRawDataSetting_01_18_30_CylindricalMine01.jpg", CV_LOAD_IMAGE_UNCHANGED);
////	// Check if image is loaded successfully
////	if (!src.data || src.empty())
////	{
////		cout << "Problem loading image!!!" << endl;
////		return EXIT_FAILURE;
////	}
////	imshow("src", src);
////	// Convert image to grayscale
////	Mat gray;
////	cvtColor(src, gray, COLOR_BGR2GRAY);
////	// Convert image to binary
////	Mat bw;
////	threshold(gray, bw, 50, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
////	// Find all the contours in the thresholded image
////	vector<Vec4i> hierarchy;
////	vector<vector<Point> > contours;
////	/* mode – Contour retrieval mode(if you use Python see also a note below).
////	CV_RETR_EXTERNAL retrieves only the extreme outer contours.
////	It sets hierarchy[i][2] = hierarchy[i][3] = -1 for all the contours.
////	CV_RETR_LIST retrieves all of the contours without establishing any hierarchical relationships.
////	CV_RETR_CCOMP retrieves all of the contours and organizes them into a two
////		- level hierarchy.At the top level, there are external boundaries of the 
////			components.At the second level, there are boundaries of the holes.
////			If there is another contour inside a hole of a connected component,
////			it is still put at the top level.
////	CV_RETR_TREE retrieves all of the contours and reconstructs a full hierarchy of nested contours.
////	This full hierarchy is built and shown in the OpenCV contours.c demo.
////		*/
////	findContours(bw, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
////	//cout << "hierarchy = " << hierarchy << "\n";
////	//--------------------------------------------------------------------------------
////	//// you could also reuse img1 here
////	Mat mask = Mat::zeros(gray.rows, gray.cols, CV_8UC1);
////	//// CV_FILLED fills the connected components found
////	//drawContours(mask, contours, -1, Scalar(255), CV_FILLED);
////	//// let's create a new image now
////	//Mat crop(src.rows, src.cols, CV_8UC3);
////	//// set background to green
////	//crop.setTo(Scalar(0, 255, 0));
////	//// and copy the magic apple
////	//src.copyTo(crop, mask);
////	//// normalize so imwrite(...)/imshow(...) shows the mask correctly!
////	//normalize(mask.clone(), mask, 0.0, 255.0, CV_MINMAX, CV_8UC1);
////	//// show the images
////	//imshow("original", src);
////	//imshow("mask", mask);
////	//imshow("canny", gray);
////	//imshow("cropped", crop);
////	//--------------------------------------------------------------------------------
////
////	//for (size_t i = 0; i < contours.size(); ++i)
////	//{
////	//	// Calculate the area of each contour
////	//	double area = contourArea(contours[i]);
////	//	// Ignore contours that are too small or too large
////	//	if (area > 1000) continue;
////	//	// Draw each contour only for visualisation purposes
////	//	//cout << "Number of contours with area > 1000 = " << contours.size() << "\n";
////
////	//	drawContours(src, contours, static_cast<int>(i), Scalar(255,0,0), 1, 8, hierarchy, 0);
////	//	// Find the orientation of each shape
////	//	//getOrientation(contours[i], src);
////	//}
////
////	//double area;
////	//Find biggest contours
////	cout << "Total number of contours = " << contours.size() << "\n";
////	/*std::vector<std::vector<cv::Point>>::const_iterator itc = contours.begin();*/
////	for (int i = 0; i< contours.size(); i++) // iterate through each contour. 
////	{
////		double a = contourArea(contours[i], false);  //  Find the area of contour
////		cout << "area size = " << a << "\n";
////		if (a>1000 /*&& a < 10000*/) {
////			//largest_area = a;
////			largest_contour_index = i;                //Store the index of largest contour
////			bounding_rect = boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
////			drawContours(mask, contours[i], static_cast<int>(i), Scalar(255, 0, 0), 1, 8, hierarchy, 0);
////		}
////	}
////	imshow("mask", mask);
////	imshow("output", src);
////	waitKey(0);
////	return 0;
////}