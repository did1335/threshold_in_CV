#include "function.h"

void mix(String WindowName,Mat &a, double alpha, Mat &b,Mat &output)
{
	newWindow(WindowName);

	double beta = 1.0 - alpha;
	addWeighted(a, alpha, b, beta,0.0,output);
	
	imshow(WindowName, output);

	return;
}