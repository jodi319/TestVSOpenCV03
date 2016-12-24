//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//
//
//using namespace cv;
//using namespace std;
//
//bool leftDown = false, leftup = false;
//Mat img, cropImg01, cropImg02;
//Point cor1, cor2;
//Rect box;
//	int i = 0;
//
//	int accessingPixelsProcess()
//	{
//		Mat src1;
//		src1 = cropImg01;
//		namedWindow("Original image", CV_WINDOW_AUTOSIZE);
//		imshow("Original image", src1);
//
//		Mat gray;
//		cvtColor(src1, gray, CV_BGR2GRAY);
//		namedWindow("Gray image", CV_WINDOW_AUTOSIZE);
//		imshow("Gray image", gray);
//
//		// know the number of channels the image has
//		cout << "original image channels: " << src1.channels() << "\n" << "gray image channels: " << gray.channels() << "\n" << endl;
//
//		// ******************* READ the Pixel intensity *********************
//		//// single channel grey scale image (type 8UC1) and pixel coordinates x=5 and y=2
//		//// by convention, {row number = y} and {column number = x}
//		//// intensity.val[0] contains a value from 0 to 255
//		//Scalar intensity1 = gray.at<uchar>(2, 5);
//		//cout << "Intensity = " << endl << " " << intensity1.val[0] << endl << endl;
//
//		//// 3 channel image with BGR color (type 8UC3)
//		//// the values can be stored in "int" or in "uchar". Here int is used.
//		//Vec3b intensity2 = src1.at<Vec3b>(10, 15);
//		//int blue = intensity2.val[0];
//		//int green = intensity2.val[1];
//		//int red = intensity2.val[2];
//		//cout << "Intensity = " << endl << " " << blue << " " << green << " " << red << endl << endl;
//
//		// ******************* WRITE to Pixel intensity **********************
//		//// This is an example in OpenCV 2.4.6.0 documentation 
//		//Mat H(10, 10, CV_64F);
//		//for (int i = 0; i < H.rows; i++)
//		//	for (int j = 0; j < H.cols; j++)
//		//		H.at<double>(i, j) = 1. / (i + j + 1);
//		//cout << H << endl << endl;
//
//		//// Modify the pixels of the BGR image
//		//for (int i = 100; i<src1.rows; i++)
//		//{
//		//	for (int j = 100; j<src1.cols; j++)
//		//	{
//		//		src1.at<Vec3b>(i, j)[0] = 0;
//		//		src1.at<Vec3b>(i, j)[1] = 200;
//		//		src1.at<Vec3b>(i, j)[2] = 0;
//		//	}
//		//}
//		//namedWindow("Modify pixel", CV_WINDOW_AUTOSIZE);
//		//imshow("Modify pixel", src1);
//
//		// ******************* CALCULATE & PLOT Histogram **********************
//		// Initialize parameters
//		int histSize = 256;		// bin size.
//								// one bin per pixel value:
//								// bin 1 = pixel intensity 0, bin 2 = pixel intensity 1, bin 3 = pixel intensity 2, etc.
//		float range[] = { 0, 255 };
//		const float *ranges[] = { range };
//
//		// Calculate histogram
//		MatND hist;
//		calcHist(&gray, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);
//		//cout << "Histogram Dimensions: " << hist.size << "\n" << "Histogram: " << hist <<  endl;
//		cout << "Width : " << hist.size().width << "\n" << endl;
//		cout << "Height: " << hist.size().height << "\n" << endl;
//		/*
//		calcHist(const Mat* images, int nimages, const int* channels, InputArray mask, OutputArray hist,
//		int dims, const int* histSize, const float** ranges, bool uniform = true, bool accumulate = false)
//		Parameters:
//		images – Source arrays.They all should have the same depth, CV_8U or CV_32F, and the same size.Each of them can have an arbitrary number of channels.
//		nimages – Number of source images.
//		channels – List of the dims channels used to compute the histogram.The first array channels are numerated from 0 to images[0].channels() - 1, the second array channels are counted from images[0].channels() to images[0].channels() + images[1].channels() - 1, and so on.
//		mask – Optional mask.If the matrix is not empty, it must be an 8 - bit array of the same size as images[i].The non - zero mask elements mark the array elements counted in the histogram.
//		hist – Output histogram, which is a dense or sparse dims - dimensional array.
//		dims – The number of parameters you want to collect data of.
//		In our example, dims = 1 because we are only counting the intensity values of each pixel (in a greyscale image).
//		histSize – Array of histogram sizes in each dimension. It is the number of subdivisions in each dim
//		ranges – Array of the dims arrays of the histogram bin boundaries in each dimension.
//		uniform - Flag indicating whether the histogram is uniform or not (see above)
//		accumulate – Accumulation flag. If it is set, the histogram is not cleared in the beginning when it is allocated.
//		This feature enables you to compute a single histogram from several sets of arrays, or
//		to update the histogram in time
//		*/
//		double total;
//		total = gray.rows * gray.cols;
//		for (int h = 0; h < histSize; h++)
//		{
//			float binVal = hist.at<float>(h);
//			cout << " " << binVal << "\n";
//		}
//
//		// Plot the histogram
//		int hist_w = 512; int hist_h = 400;
//		int bin_w = cvRound((double)hist_w / histSize);
//
//		Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
//		normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
//
//		for (int i = 1; i < histSize; i++)
//		{
//			line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
//				Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
//				Scalar(255, 0, 0), 2, 8, 0);
//		}
//
//		namedWindow("Result", 1);    imshow("Result", histImage);
//		// ******************* BRIGHTEST Spot **********************
//		//the area of the image with the largest intensity value
//		//(minVal, maxVal, minLoc, maxLoc) = cv2.minMaxLoc(gray)
//		double m, M;
//		Point p_min, p_max;
//		minMaxLoc(gray, &m, &M, &p_min, &p_max);
//		cout << "min: " << m << " at " << p_min << "\n" << endl;
//		cout << "max: " << M << " at " << p_max << "\n" << endl;
//		//cv2.circle(image, maxLoc, 5, (255, 0, 0), 2)
//		// Draw a circle 
//		circle(src1, p_max, 32.0, Scalar(0, 0, 255), 5, 8);
//		imshow("Image with circle", src1);
//
//		waitKey(0);
//		return 0;
//	}
//
//void mouse_call(int event, int x, int y, int, void*)
//{
//	if (event == EVENT_RBUTTONDBLCLK)
//	{
//		cout << "right mouse button clicked " << endl;
//		int app = accessingPixelsProcess();
//	}
//		if (event == EVENT_LBUTTONDOWN)
//		{
//			leftDown = true;
//			cor1.x = x;
//			cor1.y = y;
//			cout << "Corner 1: " << cor1 << endl;
//
//		}
//		if (event == EVENT_LBUTTONUP)
//		{
//			if (abs(x - cor1.x) > 20 && abs(y - cor1.y) > 20) //checking whether the region is too small
//			{
//				leftup = true;
//				cor2.x = x;
//				cor2.y = y;
//				cout << "Corner 2: " << cor2 << endl;
//			}
//			else
//			{
//				cout << "Select a region more than 20 pixels" << endl;
//			}
//		}
//
//		if (leftDown == true && leftup == false) //when the left button is down
//		{
//			Point pt;
//			pt.x = x;
//			pt.y = y;
//			Mat temp_img = img.clone();
//			rectangle(temp_img, cor1, pt, Scalar(0, 0, 255)); //drawing a rectangle continuously
//			imshow("Original", temp_img);
//
//		}
//		if (leftDown == true && leftup == true) //when the selection is done
//		{
//
//			box.width = abs(cor1.x - cor2.x);
//			box.height = abs(cor1.y - cor2.y);
//			box.x = min(cor1.x, cor2.x);
//			box.y = min(cor1.y, cor2.y);
//			Mat crop(img, box); //Selecting a ROI(region of interest) from the original pic
//			cout << "i = " << i << "\n";
//			if (i == 0)
//			{
//				namedWindow("Cropped Image 01");
//				imshow("Cropped Image 01", crop); //showing the cropped image 
//				cropImg01 = crop;
//				i++;
//			}
//			else
//			{
//				namedWindow("Cropped Image 02");
//				imshow("Cropped Image 02", crop); //showing the cropped image 
//				cropImg02 = crop;
//			}
//			leftDown = false;
//			leftup = false;
//
//		}
//}
//
//
//int main()
//{
//	img = imread("20161215 02.33_368.jpg");
//	namedWindow("Original");
//	imshow("Original", img);
//
//	setMouseCallback("Original", mouse_call); //setting the mouse callback for selecting the region with mouse
//	//if (cropImg01.empty())
//	//{
//
//	//}
//	//else
//	//{
//	//	imshow("My Cropped Image 01", cropImg01);
//	//	//imshow("My Cropped Image 02", cropImg01);	
//	//}
//	while (char(waitKey(1) != 'q')) //waiting for the 'q' key to finish the execution
//	{
//
//	}
//	return 0;
//}