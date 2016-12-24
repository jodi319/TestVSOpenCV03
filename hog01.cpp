//#include < opencv2\opencv.hpp>  
//#include < stdio.h>  
//
//
//#ifdef _DEBUG          
//#pragma comment(lib, "opencv_core249d.lib")  
//#pragma comment(lib, "opencv_imgproc249d.lib")   //MAT processing  
//#pragma comment(lib, "opencv_highgui249d.lib")  
//#pragma comment(lib, "opencv_objdetect249d.lib")  
//#else  
//#pragma comment(lib, "opencv_core249.lib")  
//#pragma comment(lib, "opencv_imgproc249.lib")  
//#pragma comment(lib, "opencv_highgui249.lib")  
//#pragma comment(lib, "opencv_objdetect249.lib")  
//#endif     
//
//#define M_PI 3.1415
//
//using namespace std;  
//using namespace cv;  
//
//
//Mat get_hogdescriptor_visual_image(Mat& origImg,
//                                   vector< float>& descriptorValues,
//                                   Size winSize,
//                                   Size cellSize,                                   
//                                   int scaleFactor,
//                                   double viz_factor);
//
//int main()  
//{  
//
// //image load
// Mat img1 = imread("./b1.jpg");
// Mat img2 = imread("./c5.jpg");
//
// //rgb 2 gray
// Mat img1_gray; 
// cvtColor(img1, img1_gray, CV_RGB2GRAY);
//
// Mat img2_gray; 
// cvtColor(img2, img2_gray, CV_RGB2GRAY);
//
// //resize smaller
// Mat r_img1_gray;
// resize(img1_gray, r_img1_gray, Size(64, 8));
// Mat r_img2_gray;
// resize(img2_gray, r_img2_gray, Size(64, 8));
//
//
// //extractino hog feature
// HOGDescriptor d1( Size(64,8), Size(8,8), Size(4,4), Size(4,4), 9);
// HOGDescriptor d2( Size(64,8), Size(8,8), Size(4,4), Size(4,4), 9);
// // Size(32,16), //winSize
// // Size(8,8), //blocksize
// // Size(4,4), //blockStride,
// // Size(4,4), //cellSize,
// // 9, //nbins,
//
// //hog feature compute
// vector< float> descriptorsValues1;
// vector< Point> locations1;
// d1.compute( r_img1_gray, descriptorsValues1, Size(0,0), Size(0,0), locations1);
// vector< float> descriptorsValues2;
// vector< Point> locations2;
// d2.compute( r_img2_gray, descriptorsValues2, Size(0,0), Size(0,0), locations2);
//
// //hog feature size
// //cout << descriptorsValues1.size() << endl;
//
//
// ///////////////////////
// //copy vector to mat  
// //create Mat  
// Mat A(descriptorsValues1.size(),1,CV_32FC1); 
// //copy vector to mat  
// memcpy(A.data,descriptorsValues1.data(),descriptorsValues1.size()*sizeof(float));
// //create Mat  
// Mat B(descriptorsValues2.size(),1,CV_32FC1); 
// //copy vector to mat  
// memcpy(B.data,descriptorsValues2.data(),descriptorsValues2.size()*sizeof(float));
//
//
// /////////////////////////
// //sum( sqrt( (A.-B)^2 ) )
// Mat C = A-B;
// C = C.mul(C);
// cv::sqrt(C, C);
// cv::Scalar rr = cv::sum(C);
// float rrr = rr(0);
// cout << "Distance: " << rrr << endl;
//
// 
// //hog visualization
// Mat r1 = get_hogdescriptor_visual_image(r_img1_gray, descriptorsValues1, Size(64,8), Size(4,4), 10, 3);
// Mat r2 = get_hogdescriptor_visual_image(r_img2_gray, descriptorsValues2, Size(64,8), Size(4,4), 10, 3);
//
// imshow("hog visualization1", r1);
// imshow("hog visualization2", r2);
//
// waitKey(0);
//
// return 0;
//}
//
//
//
