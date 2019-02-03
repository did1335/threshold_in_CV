#include "function.h"

const char* filename = "../data/c.jpg";//filename of image
Mat img = imread(filename);

//HSV
int iLowH = 0;
int iHighH = 179;

int iLowS = 0;
int iHighS = 255;

int iLowV = 0;
int iHighV = 255;

void create_trackbar()
{
	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);
	
	return;
}

int main(int argc, char** argv)
{	
	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	create_trackbar();

	bool trackObjects = false;
	bool useMorphOps = false;
	
	while (true)
	{
		Mat blur,imgHSV;
		GaussianBlur(img, blur, Size(3, 3), 0, 0, BORDER_DEFAULT);
		cvtColor(blur, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
		cout << "iLowH:" << iLowH << endl
			 << "iLowS:" << iLowS << endl
			 << "iLowV:" << iLowV << endl
			 << "iHighH:" << iHighH << endl
			 << "iHighS:" << iHighS << endl
			 << "iHighV:" << iHighV << endl
			 << endl;
		waitKey(20);
		
		//§ÎºA¾Ç(morphological opening¡Bmorphological closing)

		//morphological opening (remove small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (fill small holes in the foreground)
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		
		newWindow("Thresholded Image");
		newWindow("Original");
		
		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		imshow("Original", img); //show the original image
		
	    imwrite("../data/new2.jpg", imgThresholded); //delay 30ms so that screen can refresh. (Images will not appear without this waitKey() command.)
		findMinAreaRect(imgThresholded);
				
		Mat drawing,Output;
		drawing = imread("../data/contour.jpg", 1);
		newWindow("Output");
		mix("Output", img, 0.6, drawing, Output);		

		imwrite("../data/out.jpg", Output);
		if (waitKey(30) >= 0) break;
	}
	return 0;
}

