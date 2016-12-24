//#include < opencv2\opencv.hpp>  
//#include < stdio.h>  
//
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "iostream"
//#include <fstream>
//#include "opencv2/objdetect/objdetect.hpp"
//
////#ifdef _DEBUG          
////#pragma comment(lib, "opencv_core249d.lib")  
////#pragma comment(lib, "opencv_imgproc249d.lib")   //MAT processing  
////#pragma comment(lib, "opencv_highgui249d.lib")  
////#pragma comment(lib, "opencv_objdetect249d.lib")  
////#else  
////#pragma comment(lib, "opencv_core249.lib")  
////#pragma comment(lib, "opencv_imgproc249.lib")  
////#pragma comment(lib, "opencv_highgui249.lib")  
////#pragma comment(lib, "opencv_objdetect249.lib")  
////#endif     
//
//#define M_PI 3.1415
//
//using namespace std;
//using namespace cv;
//
//
//Mat get_hogdescriptor_visual_image(Mat& origImg,
//	vector< float>& descriptorValues,
//	Size winSize,
//	Size cellSize,
//	int scaleFactor,
//	double viz_factor);
//int myBinSize = 9;
//int width_threshold = 1344;
//int height_threshold = 640;
//int width_difference = 0;
//int heigth_difference = 0;
//
//int main()
//{
//
//	
//
//	Mat img1 = imread("20161215 02.32_367.jpg");
//	imshow("Source Image", img1);
//	cout << "original image width and height= " << img1.size().width << "x" << img1.size().height << "\n";
//	if (img1.size().width % 8 == 0)
//	{
//		cout << img1.size().width << " can be divided by 8 " << "\n";
//		cout << "remainder= " << img1.size().width % 8 << "\n";
//	}
//	else
//	{
//		cout << "remainder= " << img1.size().width % 8 << "\n";
//	}
//	//Mat img(512, 1024, CV_8UC3); imshow("img", img);
//	cout << "width_threshold= " << width_threshold << "\n";
//	cout << "height_threshold= " << height_threshold << "\n";
//	if (img1.size().width > width_threshold)
//	{
//		cout << "width more then threshold" << "\n";
//		cout << "img1.size().width= " << img1.size().width << "\n";
//		if (img1.size().height > height_threshold)
//		{//w>,h>
//			cout << "height more then threshold" << "\n";
//			cout << "img1.size().height= " << img1.size().height << "\n";
//		}
//		else 
//		{//w>,h<
//			cout << "height less then threshold" << "\n";
//			cout << "img1.size().heigth= " << img1.size().height << "\n";
//		}
//	}
//	else if (img1.size().height < height_threshold)
//	{
//		cout << "height less then threshold" << "\n";
//		cout << "img1.size().height= " << img1.size().height << "\n";
//		heigth_difference = height_threshold - img1.size().height;
//		cout << "height difference= " << heigth_difference << "\n";
//		if (img1.size().width < width_threshold)
//		{//w<,h<
//			cout << "width less then threshold" << "\n";
//			cout << "img1.size().width= " << img1.size().width << "\n";
//			width_difference = width_threshold - img1.size().width;
//			cout << "width difference= " << width_difference << "\n";
//		}
//		else
//		{//w>,h<
//			cout << "width more then threshold" << "\n";
//			cout << "img1.size().height= " << img1.size().height << "\n";
//		}
//	}
//	else
//	{//w=,h=
//		cout << "width and height equal threshold" << "\n";
//		cout << "img1.size().height= " << img1.size().height << "\n";
//		cout << "img1.size().width= " << img1.size().width << "\n";
//	}
//	Mat padded;
//	//int padding = 3;
//	//padded.create(height_threshold,width_threshold, img1.type());
//	//padded.setTo(cv::Scalar::all(0));
//	//imshow("padded", padded);
//	int top = (heigth_difference / 2) + heigth_difference % 2;
//	int bottom = heigth_difference / 2;
//	int left = (width_difference / 2) + width_difference % 2;
//	int right = width_difference / 2;
//	cout << "top= " << top << "\n";
//	cout << "bottom= " << bottom  << "\n";
//	cout << "left= " << left << "\n";
//	cout << "right= " << right << "\n";
//	copyMakeBorder(img1, padded, top, bottom, left, right, BORDER_CONSTANT, 0);
//	//img.copyTo(padded(Rect(padding, padding, img.cols, img.rows)));
//	imshow("Resized Gray Image", padded);
//	cout << "padded image width and height= " << padded.size().width << "x" << padded
//		.size().height << "\n";
//
//	Mat img1_gray;
//	cvtColor(padded, img1_gray, CV_RGB2GRAY);
//
//	Mat r_img1_gray;
//	r_img1_gray = img1_gray;
//	copyMakeBorder(img1_gray, padded, top, bottom, left, right, BORDER_CONSTANT, 0);
//	//resize(img1_gray, r_img1_gray, Size(64, 128));
//	imshow("(Resized)Gray Scale Image used by HOG", r_img1_gray);
//
//	//extractino hog feature
//	HOGDescriptor d1(r_img1_gray.size(), Size(64, 64), Size(32, 32), Size(32, 32), myBinSize);
//	//// Size(32,16), //winSize
//	//// Size(8,8), //blocksize
//	//// Size(4,4), //blockStride,
//	//// Size(4,4), //cellSize,
//	//// 9, //nbins,
//
//
//	//feature compare
//	vector< float> descriptorsValues1;
//	vector< Point> locations1;
//	d1.compute(r_img1_gray, descriptorsValues1, Size(0, 0), Size(0, 0), locations1);
//	size_t descrSize =  d1.getDescriptorSize();
//	cout << "descriptor size= " << descrSize << "\n";
//
//	//hog visualization
//	Mat r1 = get_hogdescriptor_visual_image(r_img1_gray,
//		descriptorsValues1,
//		r_img1_gray.size(),
//		Size(32, 32),
//		1,
//		5);
//
//	imshow("hog visualization", r1);
//	waitKey(0);
//
//	return 0;
//}
//
//bool cmpf(float A, float B, float epsilon = 0.005f)
//{
//	return (fabs(A - B) < epsilon);
//}
//
//Mat get_hogdescriptor_visual_image(Mat& origImg,
//	vector< float>& descriptorValues,
//	Size winSize,
//	Size cellSize,
//	int scaleFactor,
//	double viz_factor)
//{
//	ofstream myfile;
//	myfile.open("example.txt");
//
//	Mat visual_image;
//	resize(origImg, visual_image, Size(origImg.cols*scaleFactor, origImg.rows*scaleFactor));
//	cvtColor(visual_image, visual_image, CV_GRAY2BGR);
//
//	Mat image(visual_image.size().height, visual_image.size().width, CV_8UC3, Scalar(0, 0, 0));
//
//	int gradientBinSize = myBinSize;
//
//	// dividing 180° into 9 bins, how large (in rad) is one bin?
//	float radRangeForOneBin = 3.14 / (float)gradientBinSize;
//
//	// prepare data structure: 9 orientation / gradient strenghts for each cell
//	int cells_in_x_dir = winSize.width / cellSize.width;
//	int cells_in_y_dir = winSize.height / cellSize.height;
//
//	int totalnrofcells = cells_in_x_dir * cells_in_y_dir;
//
//	float*** gradientStrengths = new float**[cells_in_y_dir];
//	int** cellUpdateCounter = new int*[cells_in_y_dir];
//	for (int y = 0; y< cells_in_y_dir; y++)
//	{
//		gradientStrengths[y] = new float*[cells_in_x_dir];
//		cellUpdateCounter[y] = new int[cells_in_x_dir];
//		for (int x = 0; x< cells_in_x_dir; x++)
//		{
//			gradientStrengths[y][x] = new float[gradientBinSize];
//			cellUpdateCounter[y][x] = 0;
//
//			for (int bin = 0; bin< gradientBinSize; bin++)
//				gradientStrengths[y][x][bin] = 0.0;
//		}
//	}
//
//	// nr of blocks = nr of cells - 1
//	// since there is a new block on each cell (overlapping blocks!) but the last one
//	int blocks_in_x_dir = cells_in_x_dir - 1;
//	int blocks_in_y_dir = cells_in_y_dir - 1;
//
//	// compute gradient strengths per cell
//	int descriptorDataIdx = 0;
//	int cellx = 0;
//	int celly = 0;
//
//	for (int blockx = 0; blockx< blocks_in_x_dir; blockx++)
//	{
//		for (int blocky = 0; blocky< blocks_in_y_dir; blocky++)
//		{
//			// 4 cells per block ...
//			for (int cellNr = 0; cellNr< 4; cellNr++)
//			{
//				// compute corresponding cell nr
//				int cellx = blockx;
//				int celly = blocky;
//				if (cellNr == 1) celly++;
//				if (cellNr == 2) cellx++;	
//				if (cellNr == 3)
//				{
//					cellx++;
//					celly++;
//				}
//
//				for (int bin = 0; bin< gradientBinSize; bin++)
//				{
//					
//					float gradientStrength = descriptorValues[descriptorDataIdx];
//					
//					descriptorDataIdx++;
//
//					gradientStrengths[celly][cellx][bin] += gradientStrength;
//
//				} // for (all bins)
//
//
//				  // note: overlapping blocks lead to multiple updates of this sum!
//				  // we therefore keep track how often a cell was updated,
//				  // to compute average gradient strengths
//				cellUpdateCounter[celly][cellx]++;
//
//			} // for (all cells)
//
//
//		} // for (all block x pos)
//	} // for (all block y pos)
//
//
//	  // compute average gradient strengths
//	for (int celly = 0; celly< cells_in_y_dir; celly++)
//	{
//		for (int cellx = 0; cellx< cells_in_x_dir; cellx++)
//		{
//
//			float NrUpdatesForThisCell = (float)cellUpdateCounter[celly][cellx];
//
//			// compute average gradient strenghts for each gradient bin direction
//			for (int bin = 0; bin< gradientBinSize; bin++)
//			{
//				gradientStrengths[celly][cellx][bin] /= NrUpdatesForThisCell;
//			}
//		}
//	}
//
//	// draw cells
//	for (int celly = 0; celly< cells_in_y_dir; celly++)
//	{
//		for (int cellx = 0; cellx< cells_in_x_dir; cellx++)
//		{
//			int drawX = cellx * cellSize.width;
//			int drawY = celly * cellSize.height;
//
//			int mx = drawX + cellSize.width / 2;
//			int my = drawY + cellSize.height / 2;
//
//			rectangle(visual_image,
//				Point(drawX*scaleFactor, drawY*scaleFactor),
//				Point((drawX + cellSize.width)*scaleFactor,
//				(drawY + cellSize.height)*scaleFactor),
//				CV_RGB(100, 100, 100),
//				1);
//			rectangle(image,
//				Point(drawX*scaleFactor, drawY*scaleFactor),
//				Point((drawX + cellSize.width)*scaleFactor,
//				(drawY + cellSize.height)*scaleFactor),
//				CV_RGB(100, 100, 100),
//				1);
//
//			// draw in each cell all 9 gradient strengths
//			for (int bin = 0; bin< gradientBinSize; bin++)
//			{
//				float currRad = bin * radRangeForOneBin + radRangeForOneBin / 2;
//				float currRadDegrees = 180 / 3.14*currRad;
//				myfile << "BIN = " << bin << ":" << "\n";
//				myfile << " -- current direction= " << currRadDegrees << " degrees" << "\n";
//				//if ((cmpf(currRadDegrees, 90.0f)))
//				//{
//					float currentGradStrength = gradientStrengths[celly][cellx][bin];
//
//					// no line to draw?
//					if (currentGradStrength == 0)
//						continue;
//
//					float dirVecX = cos(currRad);
//					float dirVecY = sin(currRad);
//					float maxVecLen = cellSize.width / 2;
//					float scale = viz_factor; // just a visual_imagealization scale,
//											  // to see the lines better
//
//											  // compute line coordinates
//					float x1 = mx - dirVecX * currentGradStrength * maxVecLen * scale; //myfile << "x1= " << x1 << "\n";
//					float y1 = my - dirVecY * currentGradStrength * maxVecLen * scale; //myfile << "y1= " << y1 << "\n";
//					float x2 = mx + dirVecX * currentGradStrength * maxVecLen * scale; //myfile << "x2= " << x2 << "\n";
//					float y2 = my + dirVecY * currentGradStrength * maxVecLen * scale; //myfile << "y2= " << y2 << "\n";
//
//					// draw gradient visual_imagealization
//					//if (currRadDegrees == 30)
//					//{
//						myfile << "currRadDegrees= " << currRadDegrees << "\n";
//					//}
//					//cmpf(currRadDegrees, 90.0f);
//					//if (cmpf(currRadDegrees, 90.0f))
//					//{
//					//	myfile << "currRadDegrees= " << currRadDegrees << "\n";
//					//	line(visual_image,
//					//		Point(x1*scaleFactor, y1*scaleFactor),
//					//		Point(x2*scaleFactor, y2*scaleFactor),
//					//		CV_RGB(255, 0, 0),
//					//		1);
//					//	line(image,
//					//		Point(x1*scaleFactor, y1*scaleFactor),
//					//		Point(x2*scaleFactor, y2*scaleFactor),
//					//		CV_RGB(255, 0, 100),
//					//		1);
//					//}
//					//else if (cmpf(currRadDegrees, 0.0f) || cmpf(currRadDegrees, 180.0f))
//					//{
//						//myfile << "currRadDegrees= " << currRadDegrees << "\n";
//						line(visual_image,
//							Point(x1*scaleFactor, y1*scaleFactor),
//							Point(x2*scaleFactor, y2*scaleFactor),
//							CV_RGB(100, 255, 100),
//							1);
//						line(image,
//							Point(x1*scaleFactor, y1*scaleFactor),
//							Point(x2*scaleFactor, y2*scaleFactor),
//							CV_RGB(100, 255, 0),
//							1);
//					//}
//					//else
//					//{
//						//line(visual_image,
//						//	Point(x1*scaleFactor, y1*scaleFactor),
//						//	Point(x2*scaleFactor, y2*scaleFactor),
//						//	CV_RGB(0, 0, 255),
//						//	1);
//						//line(image,
//						//	Point(x1*scaleFactor, y1*scaleFactor),
//						//	Point(x2*scaleFactor, y2*scaleFactor),
//						//	CV_RGB(0, 0, 255),
//						//	1);
//					//}
//
//
//				} // for (all bins)
//
//			//} // for conditional direction drawing
//
//		} // for (cellx)
//	} // for (celly)
//
//
//	  // don't forget to free memory allocated by helper data structures!
//	for (int y = 0; y< cells_in_y_dir; y++)
//	{
//		for (int x = 0; x< cells_in_x_dir; x++)
//		{
//			delete[] gradientStrengths[y][x];
//		}
//		delete[] gradientStrengths[y];
//		delete[] cellUpdateCounter[y];
//	}
//	delete[] gradientStrengths;
//	delete[] cellUpdateCounter;
//	//myfile << "Writing this to a file.\n";
//	myfile.close();
//	return visual_image;
//	//return image;
//
//}