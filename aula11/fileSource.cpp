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
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"


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


int ex2_SIFT_AND_FAST(){

    Mat input = cv::imread("orig.jpg", 0); //Load as grayscale

    cv::SiftFeatureDetector detector_sift;
    cv::FastFeatureDetector detector_fast;

    std::vector<cv::KeyPoint> keypoints_sift;
    std::vector<cv::KeyPoint> keypoints_fast;
    detector_sift.detect(input, keypoints_sift);
    detector_fast.detect(input, keypoints_fast);

    // Add results to image and save.
    Mat output_sift, output_fast;
    cv::drawKeypoints(input, keypoints_sift, output_sift);
    cv::drawKeypoints(input, keypoints_fast, output_fast);

    namedWindow("SIFT result", CV_WINDOW_NORMAL );
    namedWindow("FAST result", CV_WINDOW_NORMAL );
    imshow("SIFT result", output_sift );
    imshow("FAST result", output_fast );

    waitKey(0);

    return 0;
}





int ex2_SURF1(){

    Mat img_1 = imread( "orig.jpg", CV_LOAD_IMAGE_GRAYSCALE );
    Mat img_2 = imread( "real.jpg", CV_LOAD_IMAGE_GRAYSCALE );

    if( !img_1.data || !img_2.data )
    { std::cout<< " --(!) Error reading images " << std::endl; return -1; }

    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;

    SurfFeatureDetector detector( minHessian );

    std::vector<KeyPoint> keypoints_1, keypoints_2;

    detector.detect( img_1, keypoints_1 );
    detector.detect( img_2, keypoints_2 );

    //-- Draw keypoints
    Mat img_keypoints_1; Mat img_keypoints_2;

    drawKeypoints( img_1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
    drawKeypoints( img_2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT );

    //-- Show detected (drawn) keypoints
    namedWindow("Keypoints 1", CV_WINDOW_NORMAL );
    namedWindow("Keypoints 2", CV_WINDOW_NORMAL );
    imshow("Keypoints 1", img_keypoints_1 );
    imshow("Keypoints 2", img_keypoints_2 );

    waitKey(0);

}


/*
* Feature Matching with FLANN
* http://docs.opencv.org/3.0-beta/doc/tutorials/features2d/feature_flann_matcher/feature_flann_matcher.html
*/

int ex2_SURF2(){

    Mat img_object = imread( "orig.jpg", CV_LOAD_IMAGE_GRAYSCALE );
    Mat img_scene = imread( "real.jpg", CV_LOAD_IMAGE_GRAYSCALE );

    if( !img_object.data || !img_scene.data ){
        std::cout<< " --(!) Error reading images " << std::endl;
        return -1;
    }

    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;

    SurfFeatureDetector detector( minHessian );

    std::vector<KeyPoint> keypoints_object, keypoints_scene;

    detector.detect( img_object, keypoints_object );
    detector.detect( img_scene, keypoints_scene );

    //-- Step 2: Calculate descriptors (feature vectors)
    SurfDescriptorExtractor extractor;

    Mat descriptors_object, descriptors_scene;

    extractor.compute( img_object, keypoints_object, descriptors_object );
    extractor.compute( img_scene, keypoints_scene, descriptors_scene );

    //-- Step 3: Matching descriptor vectors using FLANN matcher
    FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    matcher.match( descriptors_object, descriptors_scene, matches );

    double max_dist = 0; double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors_object.rows; i++ ){
        double dist = matches[i].distance;
        if( dist < min_dist )
            min_dist = dist;
        if( dist > max_dist )
            max_dist = dist;
    }

    printf("-- Max dist : %f \n", max_dist );
    printf("-- Min dist : %f \n", min_dist );

    //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
    std::vector< DMatch > good_matches;

    for( int i = 0; i < descriptors_object.rows; i++ ){
        if( matches[i].distance < 3*min_dist ){
            good_matches.push_back( matches[i]);
        }
    }

    Mat img_matches;
    drawMatches( img_object, keypoints_object, img_scene, keypoints_scene,
    good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
    vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

    //-- Localize the object
    std::vector<Point2f> obj;
    std::vector<Point2f> scene;

    for( int i = 0; i < good_matches.size(); i++ ){
        obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
    }

    Mat H = findHomography( obj, scene, CV_RANSAC );

    //-- Get the corners from the image_1 ( the object to be "detected" )
    std::vector<Point2f> obj_corners(4);
    obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( img_object.cols, 0 );
    obj_corners[2] = cvPoint( img_object.cols, img_object.rows ); obj_corners[3] = cvPoint( 0, img_object.rows );
    std::vector<Point2f> scene_corners(4);

    perspectiveTransform( obj_corners, scene_corners, H);

    //-- Draw lines between the corners (the mapped object in the scene - image_2 )
    line( img_matches, scene_corners[0] + Point2f( img_object.cols, 0), scene_corners[1] + Point2f( img_object.cols, 0), Scalar(0, 255, 0), 4 );
    line( img_matches, scene_corners[1] + Point2f( img_object.cols, 0), scene_corners[2] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
    line( img_matches, scene_corners[2] + Point2f( img_object.cols, 0), scene_corners[3] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
    line( img_matches, scene_corners[3] + Point2f( img_object.cols, 0), scene_corners[0] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );

    //-- Show detected matches
    namedWindow( "Good Matches & Object detection", CV_WINDOW_NORMAL );
    imshow( "Good Matches & Object detection", img_matches );

    waitKey(0);

    return 0;

}








