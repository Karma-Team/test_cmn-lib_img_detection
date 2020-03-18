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



int main( int argc, char** argv )
{
	VideoCapture cap("/home/ahu/Workspace/py-video-processing-rsc/video_data/finale_match_1.mp4");
	if(!cap.isOpened())
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	while(true)
	{
		// Read a new frame from video
		Mat imgOriginal;
		bool bSuccess = cap.read(imgOriginal);
		if(!bSuccess)
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		// Convert the captured frame from BGR to HSV
		Mat imgHSV;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

		// Threshold the image
		Mat imgThresholdedGreen;
		Mat imgThresholdedRedA;
		Mat imgThresholdedRedB;
		//inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
		inRange(imgHSV, Scalar(30, 75, 0),		Scalar(70, 255, 255),	imgThresholdedGreen);
		inRange(imgHSV, Scalar(0, 100, 100),	Scalar(10, 255, 255),	imgThresholdedRedA);
		inRange(imgHSV, Scalar(160, 100, 100),	Scalar(180, 255, 255),	imgThresholdedRedB);

		// Generate the final mask
		Mat imgMask;
		Mat imgThresholded;
		imgMask			= imgThresholdedGreen + imgThresholdedRedA + imgThresholdedRedB;
		imgThresholded 	= imgThresholdedGreen + imgThresholdedRedA + imgThresholdedRedB;

		// Morphological opening (remove small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		// Morphological closing (fill small holes in the foreground)
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		// Show the original and the thresholded image
		imshow("Mask Image", 		imgMask);
		imshow("Thresholded Image",	imgThresholded);
		imshow("Original Image", 	imgOriginal);

		// Wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		if(waitKey(30) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;
}
