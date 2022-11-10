#include "opencv2\opencv.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\core\core.hpp"

using namespace cv;
using namespace std;

void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		// Move elements of arr[0..i-1], 
		// that are greater than key, to one
		// position ahead of their
		// current position
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
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
	int middle;
	// we should write 2 for loops to reach each and every pixel of the image
	for (int i = adj; i < image.rows - adj; i++) {
		for (int j = adj; j < image.cols - adj; j++) {
			// then we have to loop the kernal to store them in an array, such that they are sorted and median value can be calculated
			index = 0;
			for (int g = i - adj; g <= i + adj; g++) {
				for (int h = j - adj; h <= j + adj; h++) {
					arr[index] = (int)gray.at<uchar>(g, h);
					index++;
				}
			}
			insertionSort(arr, size); //sorting the values of kernal (neghbouring and pixel itself)
			middle = size / 2;
			output.at<uchar>(i, j) = (uchar)arr[middle]; //assigning the middle value of the sorted array -> median
		}
	}

	namedWindow("Gray");
	imshow("Gray", gray);

	namedWindow("Output Image");
	imshow("Output Image", output);

	waitKey(0);

	return 0;
}