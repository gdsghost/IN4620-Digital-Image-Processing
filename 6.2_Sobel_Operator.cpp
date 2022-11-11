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

	int T = atoi(argv[2]);

	int gx = 0;
	int gy = 0;
	int G = 0;

	for (int i = 1; i < image.rows - 1; i++) {
		for (int j = 1; j < image.cols - 1; j++) {
			gx = (-1 * gray.at<uchar>(i - 1, j - 1)) + (-2 * gray.at<uchar>(i - 1, j)) + (-1 * gray.at<uchar>(i - 1, j + 1)) + (1 * gray.at<uchar>(i + 1, j - 1)) + (2 * gray.at<uchar>(i + 1, j)) + (1 * gray.at<uchar>(i + 1, j + 1));
			gy = (-1 * gray.at<uchar>(i - 1, j - 1)) + (1 * gray.at<uchar>(i - 1, j + 1)) + (-2 * gray.at<uchar>(i, j - 1)) + (2 * gray.at<uchar>(i, j + 1)) + (-1 * gray.at<uchar>(i + 1, j - 1)) + (1 * gray.at<uchar>(i + 1, j + 1));
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