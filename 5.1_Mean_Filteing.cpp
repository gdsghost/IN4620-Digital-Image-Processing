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

	Mat gray(image.rows, image.cols, CV_8UC1, Scalar(0));

	cvtColor(image, gray, COLOR_BGR2GRAY);

	Mat output = gray.clone();

	// we should write 2 for loops to reach each and every pixel of the image
	for (int i = 1; i < image.rows - 1; i++) {
		for (int j = 1; j < image.cols - 1; j++) {
			// then we have to loop the kernal to get the total of neighbouring pixels to calculate the average and place to this selected pixel
			int sum = 0;
			int avg = 0;
			for (int g = i - 1; g <= i + 1; g++) {
				for (int h = j - 1; h <= j + 1; h++) {
					sum = sum + (int)gray.at<uchar>(g, h);
				}
			}
			avg = sum / 9;
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