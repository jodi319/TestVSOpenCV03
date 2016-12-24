//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "iostream"
//#include "opencv2/objdetect/objdetect.hpp"
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	HOGDescriptor hog;
//	vector< vector < float> > v_descriptorsValues;
//	vector< vector < Point> > v_locations;
//	
//	//read image file
//	Mat img, img_gray;
//	img = imread("20161215 02.33_368.jpg");
//
//	//resizing
//	resize(img, img, Size(64, 48)); //Size(64,48) ); //Size(32*2,16*2)); //Size(80,72) ); 
//									//gray
//	cvtColor(img, img_gray, CV_RGB2GRAY);
//
//	//extract feature
//	HOGDescriptor d(Size(32, 16), Size(8, 8), Size(4, 4), Size(4, 4), 9);
//	vector< float> descriptorsValues;
//	vector< Point> locations;
//	d.compute(img_gray, descriptorsValues, Size(0, 0), Size(0, 0), locations);
//
//	printf("descriptor number =%d\n", descriptorsValues.size() );
//	v_descriptorsValues.push_back(descriptorsValues);
//	v_locations.push_back(locations);
//	//show image
//	imshow("origin", img);
//
//	waitKey(0);
//	return 0;
//}