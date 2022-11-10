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

	//Gaussian Filter
	Mat Gaus = gr.clone();
	int kernel = 5;
	// intialising standard deviation to 1.0 
	double sigma = 1.0;
	double r = 2.0 * sigma * sigma;
	double s = 2.0 * sigma * sigma;

	// sum is for normalization 
	double sum = 0.0;
	double GKernel[5][5];

	// generating 5x5 kernel 
	for (int x = -2; x <= 2; x++) {
		for (int y = -2; y <= 2; y++) {
			r = sqrt(x * x + y * y);
			GKernel[x + 2][y + 2] = (exp(-(r * r) / s)) / (3.14 * s);
			sum += GKernel[x + 2][y + 2];
		}
	}

	// normalising the Kernel 
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			GKernel[i][j] /= sum;


	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j)
			cout << GKernel[i][j] << "\t";
		cout << endl;
	}


	for (int i = kernel / 2; i < height - (kernel / 2); i++) {
		for (int j = kernel / 2; j < width - (kernel / 2); j++) {
			int sum = 0;
			for (int m = -kernel / 2; m <= kernel / 2; m++) {
				for (int n = -kernel / 2; n <= kernel / 2; n++) {
					int a = gr.at<uchar>(i + m, j + n);
					double p = GKernel[2 + m][2 + n];
					sum = sum + (p * a);
				}
			}
			Gaus.at<uchar>(i, j) = (uchar)sum;
		}
	}

	imshow("Gray Image", gr);
	imshow("Output Image", Gaus);
	imwrite("output_image.jpg", Gaus);

	waitKey(0);

	return 0;

}