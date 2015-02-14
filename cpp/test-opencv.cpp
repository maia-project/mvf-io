#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include "mvfio.h"

using namespace cv;

int main (int argc, char * argv[])
{
	MVF * video;
	Mat A, B;
	double min, max;

	// getting frame from given video
	video = new MVF (argv[1]);
	std::vector<unsigned short> f;
	video->getFrame (1, f);

	// std::vector into cv::Mat
	A = Mat (video->header.height, video->header.width, CV_16U, &f[0]);
	
	// histogram eq.
	// correct, but slow slow: minMaxIdx (A, &min, &max);
	// faster:
	min = 0;
	max = pow (2, video->header.bppUsed);
	std::cout << "min: " << min << ", max: " << max << std::endl;
	A -= min;
	A.convertTo(B, CV_8U, 255.0 / (max-min));
	
	// show the frame
	namedWindow ("MVF frame", WINDOW_AUTOSIZE );
	imshow ("MVF frame", B);
	
	// waiting for user interaction
	std::cout << "press any key" << std::endl;
	waitKey (0);

	return 0;
}
