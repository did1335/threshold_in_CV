#include "function.h"

void findMinAreaRect(Mat &threshold_output)
{
	Mat src = threshold_output;
	GaussianBlur(src,src, Size(3, 3), 0, 0);
	Mat dst1;
	Canny(src, dst1, 50, 150, 3);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(dst1, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));//尋找輪廓
	

	vector<RotatedRect> minRect(contours.size());//對每個找到的輪廓創建可傾斜邊框
	for (int i = 0; i < contours.size(); i++)
	{
		minRect[i] = minAreaRect(Mat(contours[i]));
	}
	
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);	//繪出輪廓及其可傾斜邊框

	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(255, 255, 255);
		Scalar color2 = Scalar(0, 255, 0);

		drawContours(drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());		//繪製輪廓
		Point2f rect_points[4]; minRect[i].points(rect_points);
		for (int j = 0; j < 4; j++)
			line(drawing, rect_points[j], rect_points[(j + 1) % 4], color2, 2, 8);
	}

	newWindow("Contours");
	imshow("Contours", drawing);
	imwrite("../data/contour.jpg", drawing);
	return;
}