#include "opencv2\opencv.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\core\core.hpp"

using namespace cv;
using namespace std;

int findMode(int arr[], int n)
{
      int maxValue = 0, maxCount = 0, i, j;

      for (i = 0; i < n; ++i) {
         int count = 0;
         for (j = 0; j < n; ++j) {
            if (arr[j] == arr[i])
            ++count;
         }

         if (count > maxCount) {
            maxCount = count;
            maxValue = arr[i];
         }
      }
      return maxValue;
}

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

	int size = k * k;
	int* arr = new int[size];
	int index;
	int mode;
	// we should write 2 for loops to reach each and every pixel of the image
	for (int i = adj; i < image.rows - adj; i++) {
		for (int j = adj; j < image.cols - adj; j++) {
			// then we have to loop the kernal to store them in an array, such that mode value can be calculated
			index = 0;
			for (int g = i - adj; g <= i + adj; g++) {
				for (int h = j - adj; h <= j + adj; h++) {
					arr[index] = (int)gray.at<uchar>(g, h);
					index++;
				}
			}
			mode = findMode(arr, size);
			output.at<uchar>(i, j) = (uchar)mode; //assigning the mode to the pixel
		}
	}

	namedWindow("Gray");
	imshow("Gray", gray);

	namedWindow("Output Image");
	imshow("Output Image", output);

	waitKey(0);

	return 0;
}
