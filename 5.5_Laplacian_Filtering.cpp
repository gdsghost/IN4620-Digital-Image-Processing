#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


using namespace cv;
using namespace std;


int main(int argc, char* argv[]) {

	Mat img = imread(argv[1], 1);

	if (!img.data) {
		cout << "Could not find the image!" << endl;
		return -1;
	}

	int height = img.rows;
	int width = img.cols;
	int widthstep = img.step;

	int ch = img.channels();

	Mat gr(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gr, COLOR_BGR2GRAY);

	//Laplacian Operator
	Mat Lap = gr.clone();
	int kernel = 3;
	int lapMask[3][3] = {
		{-1 , -1 , -1 },
		{-1 , 8 , -1 },
		{ -1 , -1 , -1 }
	};

	for (int i = kernel / 2; i < height - kernel / 2; i++) {
		for (int j = kernel / 2; j < width - kernel / 2; j++) {
			int sum = 0;
			for (int k = -kernel / 2; k <= kernel / 2; k++) {
				for (int l = -kernel / 2; l <= kernel / 2; l++) {
					int val = gr.at<uchar>(i + k, j + l);
					sum += cvRound(lapMask[k + (kernel / 2)][l + (kernel / 2)] * val);
				}
			}
			if (sum < 0) {
				sum = 0;
			}
			else if (sum > 255) {
				sum = 255;
			}

			Lap.at<uchar>(i, j) = sum;
		}
	}

	imshow("Gray Image", gr);
	imshow("Output Image", Lap);
	imwrite("output_image.jpg", Lap);

	waitKey(0);

	return 0;

}