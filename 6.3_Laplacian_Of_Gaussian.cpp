#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {

	Mat img = imread(argv[1], IMREAD_GRAYSCALE);

	if (!img.data) {
		cout << "Could not find the image!" << endl;
		return -1;
	}

	//Gaussian smmothing
	Mat smooth = img.clone();

	int k[5][5] = { {2, 4, 5, 4, 2},
					{4, 9, 12, 9, 4},
					{5, 12, 15, 12, 5},
					{ 4, 9, 12, 9, 4 },
					{ 2, 4, 5, 4, 2 } };

	double val;
	for (int i = 2; i < img.rows - 2; i++) {
		for (int j = 2; j < img.cols - 2; j++) {
			val = 0.0;
			for (int m = -2; m <= 2; m++) {
				for (int n = -2; n <= 2; n++) {
					val = val + double(k[m + 2][n + 2] * img.at<uchar>(i + m, j + n)) / 159;
				}
			}
			smooth.at<uchar>(i, j) = cvRound(val);
		}
	}

	Mat output = img.clone();
	
	//Laplacian Operator
	int gx = 0;
	for (int i = 1; i < img.rows - 1; i++) {
		for (int j = 1; j < img.cols - 1; j++) {
			gx = -smooth.at<uchar>(i - 1, j - 1) - smooth.at<uchar>(i, j - 1) - smooth.at<uchar>(i + 1, j - 1) - smooth.at<uchar>(i - 1, j) + 8 * smooth.at<uchar>(i, j) - smooth.at<uchar>(i + 1, j) - smooth.at<uchar>(i - 1, j + 1) - smooth.at<uchar>(i, j + 1) - smooth.at<uchar>(i + 1, j + 1);
			if (gx < 0) {
				gx = 0;
			}
			else if (gx > 255) {
				gx = 255;
			}
			output.at<uchar>(i, j) = gx;
		}
	}

	namedWindow("Original Image");
	imshow("Original Image", img);

	namedWindow("Smoothed Image");
	imshow("Smoothed Image", smooth);

	imshow("Output Image", output);
	imwrite("output_image.jpg", output);

	waitKey(0);

	return 0;

}