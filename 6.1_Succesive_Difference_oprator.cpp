#include "opencv2\opencv.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\core\core.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {

	Mat image = imread(argv[1]);

	if (!image.data) {
		cout << "Couldn't open or find the image!" << endl;
		return -1;
	}
	
		//----to manupulate color image directly we can access individual channels as below-------------------------------
	int r = image.at<Vec3b>(1, 1)[0];
	int g = image.at<Vec3b>(1, 1)[1];
	int b = image.at<Vec3b>(1, 1)[2];
	//----such that inside the for loop, we can assign our value to individual pixel values of individual channels----

	Mat gray(image.rows, image.cols, CV_8UC1, Scalar(0));

	cvtColor(image, gray, COLOR_BGR2GRAY);

	Mat output = gray.clone();

	int T = atoi(argv[2]);

	int gx = 0;
	int gy = 0;
	int G = 0;

	for (int i = 0; i < image.rows - 1; i++) {
		for (int j = 0; j < image.cols - 1; j++) {
			gx = gray.at<uchar>(i, j) - gray.at<uchar>(i, j + 1);
			gy = gray.at<uchar>(i, j) - gray.at<uchar>(i + 1, j);
			G = abs(gx) + abs(gy);

			if (G > T) {
				output.at<uchar>(i, j) = 255;
			}
			else {
				output.at<uchar>(i, j) = 0;
			}
		}
	}



	namedWindow("Gray");
	imshow("Gray", gray);

	namedWindow("Output Image");
	imshow("Output Image", output);

	waitKey(0);

	return 0;
}