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

    cout<< " 0: Valor de ratio Threshold:" << endl;
    cout<< "q - exit" << endl;



    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera



        int ratiothresh = 30;
        int key = waitKey(10);



        cvtColor(frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, ratiothresh, 3);
        imshow("edges", edges);

        switch((char)key){
            case '10' : ratiothresh = 10; break;
            case '20' : ratiothresh = 20; break;
            case '30' : ratiothresh = 30; break;
            case '40' : ratiothresh = 40; break;
            case '50' : ratiothresh = 50; break;
        }

        if((char)key == 'q') { break; }

        if(waitKey(30) >= 0) break;
    }
    return 0;

}

/*
    falta acertar parametros para ficar top ou mete-los alteráveis de modo a adaptar-se a cada situacao..
*/
int ex4(){

    int thresh = 240;
    Mat dst, dst_norm, dst_norm_scaled;

    /// Detector parameters
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat gray;
    for(;;){
        Mat frame;
        cap >> frame; // get a new frame from camera


        cvtColor( frame, gray, COLOR_BGR2GRAY);


        dst = Mat::zeros( frame.size(), CV_32FC1 );

        /// Detecting corners
        cornerHarris( gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );

        /// Normalizing
        normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
        convertScaleAbs( dst_norm, dst_norm_scaled );

        /// Drawing a circle around corners
        for( int j = 0; j < dst_norm.rows ; j++ ){
            for( int i = 0; i < dst_norm.cols; i++ ){
                if( (int) dst_norm.at<float>(j,i) > thresh ){
                    circle( dst_norm_scaled, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
                }
            }
        }

        imshow("Result #4", dst_norm_scaled);

        if(waitKey(30) >= 0) break;
    }
    return 0;

}


/*
*   Para este exercicios falta meter no loop para que seja possivel ajustar o valor de thresh para cada imagem.
*/
int ex5(){

    Mat frame, src_gray, src_bin;
    int thresh = 80;
    RNG rng(12345);
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;


    frame = imread("../images/bolas.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file

    cvtColor( frame, src_gray, CV_BGR2GRAY );

    blur( src_gray, src_gray, Size(3,3) );

    /// Detect edges using Threshold
    threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );

    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Approximate contours to polygons + get bounding rects and circles
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    vector<Point2f>center( contours.size() );
    vector<float>radius( contours.size() );

    for( int i = 0; i < contours.size(); i++ ) {
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
    }


    /// Draw polygonal contour + bonding rects + circles
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ ){
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        //drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
        //rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
        circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
    }


    namedWindow( "Orignal #5", CV_WINDOW_AUTOSIZE );
    namedWindow( "Result #5", CV_WINDOW_AUTOSIZE );

    imshow("Orignal #5", frame);
    imshow("Result #5", drawing);

    waitKey(0);

    return 0;

}


/*
* Hough Line Transform
* http://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_lines/hough_lines.html
*/
int ex6_1(){

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat gray;
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera


        Mat dst, cdst;
        Canny(frame, dst, 50, 200, 3);
        cvtColor(dst, cdst, CV_GRAY2BGR);

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


        imshow("Hough Line Transform", cdst);

        if(waitKey(30) >= 0) break;
    }
    return 0;

}

/*
* Hough Circle Transform
* http://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html
*/
int ex6_2(){



    Mat src_gray, src;

    src = imread("../images/moedas.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file


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

    waitKey(0);

    return 0;

}


