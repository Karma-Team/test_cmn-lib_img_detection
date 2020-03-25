//============================================================================
// Name        : test_cmn-lib_img_detection.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================



#include <iostream>
/*
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/flann.hpp>
#include <opencv2/gapi.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/photo.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
*/
#include <IMG_Detection.hpp>



using namespace std;
using namespace cv;
using namespace IMG;



int main( int argc, char** argv )
{
	cout << "Test C++ library for img detection" << endl;

	VideoCapture	l_videoCapture;
	Mat 			l_inImgCamera;
	CDetection 		l_detection;

	bool l_readVideoSuccess;

	// Open the video
		l_videoCapture.open("/home/ahu/Workspace/py-video-processing-rsc/video_data/finale_match_1.mp4");
		if(!l_videoCapture.isOpened())
		{
			cout << "Cannot open the the video" << endl;
			return 0;
		}

	// Read a video frame and convert it from BGR to HSV
		do
		{
			l_readVideoSuccess = l_videoCapture.read(l_inImgCamera);

			if(l_readVideoSuccess == true)
			{
				l_detection.cupsDetection(l_inImgCamera);
			}
		}
		while(l_readVideoSuccess == true);

	return 0;
}
