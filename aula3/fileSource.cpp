#include "fileSource.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int findBiggestContour(vector<vector<Point> >);



int ex1(){


    double maxValue, valueC;
    int thresholdType, adaptiveMethod, blockSize;

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    cout<< "MaxValue(!=0) : "<< endl;
    cin>>maxValue;

    cout<< "ThresholdType(ADAPTIVE_THRESH_MEAN_C = 0 , ADAPTIVE_THRESH_GAUSSIAN_C = 1)" << endl;
    cin>>thresholdType;

    cout<< "AdaptiveMethod (THRESH_BINARY = 0 , THRESH_BINARY_INV = 1) "<< endl;
    cin>>adaptiveMethod;

    cout<< " BlockSize (3, 5, 7, and so on)"<< endl;
    cin>>blockSize;

    cout<< " C (Normally, it is positive)"<< endl;
    cin>>valueC;

    Mat frameThreshold, frameGray;

    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera

        cvtColor(frame, frameGray, CV_BGR2GRAY);
        adaptiveThreshold( frameGray, frameThreshold, maxValue ,thresholdType,adaptiveMethod,blockSize, valueC );

        imshow("frameGray", frameGray);
        imshow("frameThreshold", frameThreshold);
        if(waitKey(30) >= 0) break;
    }
    return 0;

}


int ex2(){

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    cout<< " 0: Binary\n 1: Binary Inverted\n 2: Threshold Truncated\n 3: Threshold to Zero\n 4: Threshold to Zero Inverted "<< endl;
    cout<< "q - exit" << endl;

    Mat frameResult;
    int type_bin;


    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera

        cvtColor(frame, frameResult, CV_BGR2GRAY);

        threshold( frameResult, frameResult, 100, 255,type_bin);

        imshow("frameResult", frameResult);

        int key = waitKey(10);

        switch((char)key){
            case '0' : type_bin=0; break;
            case '1' : type_bin=1; break;
            case '2' : type_bin=2; break;
            case '3' : type_bin=3; break;
            case '4' : type_bin=4; break;
        }

        if((char)key == 'q') { break; }

    }
    return 0;

}



int ex3(){

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frameResult;
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera

        blur( frame, frame, Size(3,3) );

        Mat hsv;
        cvtColor(frame, hsv, CV_BGR2HSV);

        Mat bw;
        inRange(hsv, Scalar(0, 10, 60), Scalar(20, 150, 255), bw);
        imshow("src", frame);
        imshow("dst", bw);

        Mat canny_output;
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        findContours( bw, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
        int s = findBiggestContour(contours);

        Mat drawing = Mat::zeros( frame.size(), CV_8UC1 );
        drawContours( drawing, contours, s, Scalar(255), -1, 8, hierarchy, 0, Point() );

        imshow("drw", drawing);

        if(waitKey(30) >= 0) break;

    }
    return 0;



}

int findBiggestContour(vector<vector<Point> > contours){
    int indexOfBiggestContour = -1;
    int sizeOfBiggestContour = 0;
    for (int i = 0; i < contours.size(); i++){
        if(contours[i].size() > sizeOfBiggestContour){
            sizeOfBiggestContour = contours[i].size();
            indexOfBiggestContour = i;
        }
    }
    return indexOfBiggestContour;
}


int ex4(){

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frameResult;
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera

        //medianBlur ( frame, frameResult, 15 );
        blur( frame, frameResult, Size( 10, 10 ), Point(-1,-1) );
        //  gaussianBlur( frame, frameResult, 15 );

        imshow("frameResult", frameResult);
        if(waitKey(30) >= 0) break;
    }
    return 0;

}


int ex5(){

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat src;
        cap >> src; // get a new frame from camera

        if( !src.data )
        { return -1; }

        /// Separate the image in 3 places ( B, G and R )
        vector<Mat> bgr_planes;
        split( src, bgr_planes );

        /// Establish the number of bins
        int histSize = 256;

        /// Set the ranges ( for B,G,R) )
        float range[] = { 0, 256 } ;
        const float* histRange = { range };

        bool uniform = true; bool accumulate = false;

        Mat b_hist, g_hist, r_hist;

        /// Compute the histograms:
        calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

        // Draw the histograms for B, G and R
        int hist_w = 512; int hist_h = 400;
        int bin_w = cvRound( (double) hist_w/histSize );

        Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

        /// Normalize the result to [ 0, histImage.rows ]
        normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

        /// Draw for each channel
        for( int i = 1; i < histSize; i++ )
        {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                   Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                   Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                   Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                   Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                   Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                   Scalar( 0, 0, 255), 2, 8, 0  );
        }

        /// Display
        namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
        imshow("calcHist Demo", histImage );


        imshow("Source", src);
        if(waitKey(30) >= 0) break;
    }
    return 0;

}



int ex6(){

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat dst;
    namedWindow("edges",1);
    for(;;)
    {
        Mat src;
        cap >> src;

        char* source_window = "Source image";
        char* equalized_window = "Equalized Image";


        if( !src.data ){
            return -1;
        }

        cvtColor(src, src, CV_BGR2GRAY);

        equalizeHist( src, dst );

        /// Display results
        namedWindow( source_window, CV_WINDOW_AUTOSIZE );
        namedWindow( equalized_window, CV_WINDOW_AUTOSIZE );

        imshow( source_window, src );
        imshow( equalized_window, dst );



        if(waitKey(30) >= 0) break;
    }
    return 0;

}


int ex7(){

    for(;;)
    {

        /// imagens com mesmas dimensoes
         Mat src1 = imread("../images/lena.jpg");
         Mat src2 = imread("../images/lenainverted.jpg");

         if( !src1.data ) {  return -1; }
         if( !src2.data ) {  return -1; }

        //image1
        /// Separate the image in 3 places ( B, G and R )
        vector<Mat> bgr_planes;
        split( src1, bgr_planes );

        /// Establish the number of bins
        int histSize = 256;

        /// Set the ranges ( for B,G,R) )
        float range[] = { 0, 256 } ;
        const float* histRange = { range };

        bool uniform = true; bool accumulate = false;

        Mat b_hist, g_hist, r_hist;

        /// Compute the histograms:
        calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

        // Draw the histograms for B, G and R
        int hist_w = 512; int hist_h = 400;
        int bin_w = cvRound( (double) hist_w/histSize );

        Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

        /// Normalize the result to [ 0, histImage.rows ]
        normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

        /// Draw for each channel
        for( int i = 1; i < histSize; i++ ){
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                   Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                   Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                   Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                   Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                   Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                   Scalar( 0, 0, 255), 2, 8, 0  );
        }

        //CÓPIA IMAGEM 2
        /// Separate the image in 3 places ( B, G and R )
        vector<Mat> bgr_planes2;
        split( src2, bgr_planes2 );

        /// Establish the number of bins
        int histSize2 = 256;

        /// Set the ranges ( for B,G,R) )
        float range2[] = { 0, 256 } ;
        const float* histRange2 = { range };

        bool uniform2 = true; bool accumulate2 = false;

        Mat b_hist2, g_hist2, r_hist2;

        /// Compute the histograms:
        calcHist( &bgr_planes2[0], 1, 0, Mat(), b_hist2, 1, &histSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes2[1], 1, 0, Mat(), g_hist2, 1, &histSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes2[2], 1, 0, Mat(), r_hist2, 1, &histSize, &histRange, uniform, accumulate );

        // Draw the histograms for B, G and R
        int hist_w2 = 512; int hist_h2 = 400;
        int bin_w2 = cvRound( (double) hist_w/histSize );

        Mat histImage2( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

        /// Normalize the result to [ 0, histImage.rows ]
        normalize(b_hist2, b_hist2, 0, histImage2.rows, NORM_MINMAX, -1, Mat() );
        normalize(g_hist2, g_hist2, 0, histImage2.rows, NORM_MINMAX, -1, Mat() );
        normalize(r_hist2, r_hist2, 0, histImage2.rows, NORM_MINMAX, -1, Mat() );

        /// Draw for each channel
        for( int i = 1; i < histSize; i++ ){
        line( histImage2, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                   Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                   Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage2, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                   Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                   Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage2, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                   Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                   Scalar( 0, 0, 255), 2, 8, 0  );
        }

        /// Display
        namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
        imshow("calcHist Demo", histImage );
        namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
        imshow("calcHist Inverted", histImage2 );

        imshow("lenaHist", src1);
        imshow("lenaHistInverted", src2);
        if(waitKey(30) >= 0) break;
    }
    return 0;

}

