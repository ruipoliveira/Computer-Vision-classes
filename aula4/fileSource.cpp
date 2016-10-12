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
        //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
        Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( grad_x, abs_grad_x );

        /// Gradient Y
        //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
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

        imshow( "Apply Laplace function", abs_dst );

        if(waitKey(30) >= 0) break;
    }

    return 0;

}






int ex3(){

    Mat src, src_gray;
    Mat dst, detected_edges;

    int edgeThresh = 1;
    int lowThreshold;
    int const max_lowThreshold = 100;
    int ratio = 3;
    int kernel_size = 3;
    char* window_name = "Edge Map";


    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera

        frame.create( frame.size(), frame.type() );

        /// Convert the image to grayscale
        cvtColor( frame, src_gray, CV_BGR2GRAY );

        /// Create a window
        namedWindow( window_name, CV_WINDOW_AUTOSIZE );

        /// Create a Trackbar for user to enter threshold

        createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

        /// Show the image
  blur( src_gray, detected_edges, Size(3,3) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);

  src.copyTo( dst, detected_edges);
  imshow( window_name, dst );



        if(waitKey(30) >= 0) break;
    }
    return 0;

}


int ex4(){

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera

        //medianBlur ( frame, edges, 15 );
        blur( frame, edges, Size( 10, 10 ), Point(-1,-1) );


        //gaussianBlur( frame, edges, 15 );

        imshow("edges", edges);
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


        imshow("edges", src);
        if(waitKey(30) >= 0) break;
    }
    return 0;

}


int ex5_2(){
}


int ex6(){

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges, dst;
    namedWindow("edges",1);
    for(;;)
    {
        Mat src;
        cap >> src; // get a new frame from camera


char* source_window = "Source image";
  char* equalized_window = "Equalized Image";
/// Apply Histogram Equalization


        if( !src.data )
        { return -1; }

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
        for( int i = 1; i < histSize; i++ )
        {
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

