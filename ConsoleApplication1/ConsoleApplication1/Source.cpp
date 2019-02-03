/**
* @file Morphology_1.cpp
* @brief Erosion and Dilation sample code
* @author OpenCV team
*/

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

#include "function.h"

using namespace std;
using namespace cv;


/* Global variables*/
Mat src, erosion_dst, dilation_dst;
int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

/** Function Headers */
//���function.h��
/*
void Erosion(int, void*);
void Dilation(int, void*);
*/


/**
* @function main
*/
int main(int argc, char** argv)
{
	/// Load an image
	CommandLineParser parser(argc, argv, "{@input | ../data/Figure.png | input image}");
	src = imread(parser.get<String>("@input"), IMREAD_COLOR);
	if (src.empty())//�p�GŪ������ɴN�����{��
	{
		cout << "Could not open or find the image!\n" << endl;
		cout << "Usage: " << argv[0] << " <Input image>" << endl;
		return -1;
	}
	
	/// Create windows
	namedWindow("Erosion Demo", WINDOW_AUTOSIZE);
	namedWindow("Dilation Demo", WINDOW_AUTOSIZE);

	//��l��
	namedWindow("Original", WINDOW_AUTOSIZE);//�s�W��l�ϵ���
	imshow("Original", src);//��ܭ�l�ϩ�Oringinal����

	//�Ƕ���
	Mat gray_image; //�ŧi�Ƕ��Ϫ�����
	cvtColor(src, gray_image, CV_BGR2GRAY);//BGR�ഫ���Ƕ�
	imwrite("../data/Gray1.jpg",gray_image);//�x�s�ഫ�᪺����
	if (gray_image.empty())//�p�GŪ������ɴN�����{��
	{
		cout << "Could not open or find the image!\n" << endl;
		cout << "Usage: " << argv[0] << " <Input image>" << endl;
		return -2;//�Ǧ^�Ȭ�2
	}
	namedWindow("Gray", CV_WINDOW_AUTOSIZE);//�Ƕ��ϵ���
	imshow("Gray", gray_image);//���gray_image����
	
	//�����w��
	/*�ۤ��e��src.cols(����)
	  �ۤ�����src.rows(����)*/
	moveWindow("Original", 0, 0);
	moveWindow("Gray", src.cols,0);
	moveWindow("Dilation Demo", 0, 1.12*src.rows);
	moveWindow("Erosion Demo", src.cols, 1.12*src.rows);


	/// Create Erosion Trackbar
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
		&erosion_elem, max_elem,
		Erosion);

	createTrackbar("Kernel size:\n 2n +1", "Erosion Demo",
		&erosion_size, max_kernel_size,
		Erosion);

	/// Create Dilation Trackbar
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
		&dilation_elem, max_elem,
		Dilation);

	createTrackbar("Kernel size:\n 2n +1", "Dilation Demo",
		&dilation_size, max_kernel_size,
		Dilation);

	/// Default start
	Erosion(0, 0);
	Dilation(0, 0);

	waitKey(0);
	return 0;
}


//�I�k
void Erosion(int, void*)
{
	int erosion_type = 0;
	if (erosion_elem == 0) { erosion_type = MORPH_RECT; }
	else if (erosion_elem == 1) { erosion_type = MORPH_CROSS; }
	else if (erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

	//![kernel]
	Mat element = getStructuringElement(erosion_type,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));
	//![kernel]

	/// Apply the erosion operation
	erode(src, erosion_dst, element);
	imshow("Erosion Demo", erosion_dst);
}
//![erosion]


//����
//![dilation]
/**
* @function Dilation
*/
void Dilation(int, void*)
{
	int dilation_type = 0;
	if (dilation_elem == 0) { dilation_type = MORPH_RECT; }
	else if (dilation_elem == 1) { dilation_type = MORPH_CROSS; }
	else if (dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement(dilation_type,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));

	/// Apply the dilation operation
	dilate(src, dilation_dst, element);
	imshow("Dilation Demo", dilation_dst);
}
//![dilation]
