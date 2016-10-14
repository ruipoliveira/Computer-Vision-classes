#include "fileSource.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void CannyThreshold(int, void*);

int ex1(){


    double maxValue, valueC;
    int thresholdType, adaptiveMethod, blockSize;

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat src, src_gray;
    Mat grad;
    char* window_name = "Sobel Demo - Simple Edge Detector";
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;


    Mat frameThreshold, frameGray;

    for(;;)
    {
        Mat src;
        cap >> src; // get a new frame from camera

        GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

        /// Convert it to gray
        cvtColor( src, src_gray, CV_BGR2GRAY );

        /// Create window
        namedWindow( window_name, CV_WINDOW_AUTOSIZE );

        /// Generate grad_x and grad_y
        Mat grad_x, grad_y;
        Mat abs_grad_x, abs_grad_y;

        /// Gradient X
        Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
        Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( grad_x, abs_grad_x );

        /// Gradient Y
        Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
        Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( grad_y, abs_grad_y );

        /// Total Gradient (approximate)
        addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

        imshow( window_name, grad );

        if(waitKey(30) >= 0) break;
    }
    return 0;

}


int ex2(){

    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat src_gray, dst;

    for(;;) {
        Mat frame;
        cap >> frame; // get a new frame from camera

        GaussianBlur( frame, frame, Size(3,3), 0, 0, BORDER_DEFAULT );

        /// Convert the image to grayscale
        cvtColor( frame, src_gray, CV_BGR2GRAY );

        /// Apply Laplace function
        Mat abs_dst;

        Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( dst, abs_dst );

        imshow("Apply Laplace function", abs_dst );

        if(waitKey(30) >= 0) break;
    }

    return 0;

}






int ex3(){

    Mat src, src_gray;
    Mat dst, detected_edges;


    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera

        cvtColor(frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 60, 3);
        imshow("edges", edges);

        if(waitKey(30) >= 0) break;
    }
    return 0;

}


int ex4(){

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat gray;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera




        if(waitKey(30) >= 0) break;
    }
    return 0;

}




int ex5(){

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat gray;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera







        if(waitKey(30) >= 0) break;
    }
    return 0;

}



int ex6(){

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat gray;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera







        if(waitKey(30) >= 0) break;
    }
    return 0;

}


