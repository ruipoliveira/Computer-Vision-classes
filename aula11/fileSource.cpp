#include "fileSource.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <unistd.h>

using namespace cv;
using namespace std;


int ex1_1(){


    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat gray;
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera


        Mat dst, cdst, cdst2;
        Canny(frame, dst, 50, 200, 3);
        cvtColor(dst, cdst, CV_GRAY2BGR);
        cvtColor(dst, cdst2, CV_GRAY2BGR);

        #if 0
        vector<Vec2f> lines;
        HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );

        for( size_t i = 0; i < lines.size(); i++ ){
            float rho = lines[i][0], theta = lines[i][1];
            Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            pt1.x = cvRound(x0 + 1000*(-b));
            pt1.y = cvRound(y0 + 1000*(a));
            pt2.x = cvRound(x0 - 1000*(-b));
            pt2.y = cvRound(y0 - 1000*(a));
            line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
        }
        #else

        vector<Vec4i> lines;

        HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );

        for( size_t i = 0; i < lines.size(); i++ ){
            Vec4i l = lines[i];
            line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
        }
        #endif

        //Outra Transformada de Hough
        vector<Vec4i> lines2;
        HoughLinesP(dst, lines2, 1, CV_PI/180, 100, 0, 0 );

        for( size_t i = 0; i < lines2.size(); i++ ){
            Vec4i l = lines2[i];
            line( cdst2, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,255,0), 3, CV_AA);
        }
        //endif

        imshow("source", frame);
        imshow("Hough Line Transform", cdst);
        imshow("Hough Line Transform2", cdst2);

        if(waitKey(30) >= 0) break;
    }
    return 0;

}


int ex1_2(){

 VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat gray;
    for(;;)
    {
        Mat src;
        cap >> src; // get a new frame from camera


        Mat src_gray;
        //Canny(src, src_gray, 50, 200, 3);
        //cvtColor(src, src_gray, CV_GRAY2BGR);


    //Mat src_gray, src;

    //src = imread("../images/moedas.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file


    /// Convert it to gray
    cvtColor( src, src_gray, CV_BGR2GRAY );

    /// Reduce the noise so we avoid false circle detection
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

    vector<Vec3f> circles;

    /// Apply the Hough Transform to find the circles
    HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200, 100, 0, 0 );

    /// Draw the circles detected
    for( size_t i = 0; i < circles.size(); i++ ){
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle center
        circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }



    imshow("Hough Circle Transform", src);

    if(waitKey(30) >= 0) break;
    }

    return 0;

}


int ex2(){

}








