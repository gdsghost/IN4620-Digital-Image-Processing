#include <iostream>
#include <stdio.h>
#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
	Mat img = imread("cat.jpg");
	if (!img.data) {
		cout << "Could not load image file:" << argv[1] << std::endl;
		waitKey(0);
		return -1;
	}

	Mat gr;
	cvtColor(img, gr, CV_BGR2GRAY, 0);//convert to gray image

	int h = gr.rows;
	int w = gr.cols;
	int N = h*w; //No of pixels in an image
	int x = 0;
	double y = 0.0;
	cout << "Width: " << w << endl;
	cout << "Height: " << h << endl;

	Mat med = gr.clone(); //Copy of image of the Histogram equilasation 
	int Gx = 0;
	int Gy = 0;
	int G = 0;
	int T = 30;


	for (int i = 1;i < h - 1;i++) {            // take median of 3x3
		for (int j = 1;j < w - 1;j++) {
			Gx = gr.at<uchar>(i, j) -1* gr.at<uchar>(i+1, j+1) ;
			Gy = gr.at<uchar>(i, j+1)-gr.at<uchar>(i+1 , j);
			G = abs(Gx) + abs(Gy);
			if (G >= T)
				med.at<uchar>(i, j) = 0;
			else
				med.at<uchar>(i, j) = 255;
		}
	}

	namedWindow("Display Window", WINDOW_AUTOSIZE);//create a window for display
	imshow("Display Window", med); //show our image inside it
	namedWindow("Display Gray", WINDOW_AUTOSIZE);//create a window for display
	imshow("Display Gray", gr); //show our image inside it
	waitKey(0);//wait for a key input and hold
	med.release();
	gr.release();
	return 0;
}