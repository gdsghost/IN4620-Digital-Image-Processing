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

	Mat output = gr.clone();

	int gx = 0;

	//Laplacian Operator

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			gx = -gr.at<uchar>(i - 1, j - 1) - gr.at<uchar>(i, j - 1) - gr.at<uchar>(i + 1, j - 1) - gr.at<uchar>(i - 1, j) + 8 * gr.at<uchar>(i, j) - gr.at<uchar>(i + 1, j) - gr.at<uchar>(i - 1, j + 1) - gr.at<uchar>(i, j + 1) - gr.at<uchar>(i + 1, j + 1);
			if (gx < 0) {
				gx = 0;
			}
			else if (gx > 255) {
				gx = 255;
			}
			output.at<uchar>(i, j) = gx;
		}
	}

	namedWindow("Gray Image");
	imshow("Gray Image", gr);
	namedWindow("Output Image");

	imshow("Output Image", output);
	imwrite("output_image.jpg", output);

	waitKey(0);

	return 0;

}