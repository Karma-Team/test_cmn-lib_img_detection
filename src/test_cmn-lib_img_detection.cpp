//============================================================================
// Name        : test_cmn-lib_img_detection.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================



#include <iostream>
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



using namespace std;
using namespace cv;



int main()
{
	VideoCapture cap("/home/ahu/Workspace/py-video-processing-rsc/video_data/finale_match_1.mp4");

	// if not success, exit program
	if(!cap.isOpened())
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	while(true)
	{
		Mat frameOriginal;
		Mat FrameFliped;

		// read a new frame from video
		bool bSuccess = cap.read(frameOriginal);

		// if not success, break loop
		if(!bSuccess)
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		// Laterally invert the image / flip the image
		flip(frameOriginal, FrameFliped, 1);
		flip(FrameFliped, FrameFliped, 1);

		// Converting image from BGR to HSV color space.
		Mat frameHsv;
		cvtColor(FrameFliped, frameHsv, COLOR_BGR2HSV);

		// Creating masks to detect the upper and lower red color.
		Mat mask, l_lower_hue_range_red, l_upper_hue_range_red;
		inRange(frameHsv, Scalar(0, 100, 100),		Scalar(10, 255, 255),	l_lower_hue_range_red);
		inRange(frameHsv, Scalar(160, 100, 100),	Scalar(180, 255, 255),	l_upper_hue_range_red);

		// Generating the final mask
		mask = l_lower_hue_range_red + l_upper_hue_range_red;

		imshow("Thresholded Image", mask);	// Show the thresholded image
		imshow("Original", FrameFliped);	// Show the original image

		// Wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		if(waitKey(30) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;
}
