#include "opencv2\opencv.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\core\core.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Enter exeFileName ImageName kernamSize");
		return -1;
	}

	Mat image = imread(argv[1]);

	if (!image.data) {
		cout << "Couldn't open or find the image!" << endl;
		return -1;
	}

	Mat gray(image.rows, image.cols, CV_8UC1, Scalar(0));

	cvtColor(image, gray, COLOR_BGR2GRAY);

	Mat output = gray.clone();

	//get the kernal size using command line and adjesment value
	int k = atoi(argv[2]);
	int adj = k / 2;

	int sum;
	int avg = 0;
	// we should write 2 for loops to reach each and every pixel of the image
	for (int i = adj; i < image.rows - adj; i++) {
		for (int j = adj; j < image.cols - adj; j++) {
			// then we have to loop the kernal to get the total of neighbouring pixels to calculate the average and place to this selected pixel
			sum = 0;
			for (int g = i - adj; g <= i + adj; g++) {
				for (int h = j - adj; h <= j + adj; h++) {
					sum = sum + (int)gray.at<uchar>(g, h);
				}
			}
			avg = sum / (k * k);
			output.at<uchar>(i, j) = (uchar)avg;
		}
	}

	namedWindow("Gray");
	imshow("Gray", gray);

	namedWindow("Output Image");
	imshow("Output Image", output);

	waitKey(0);

	return 0;
}