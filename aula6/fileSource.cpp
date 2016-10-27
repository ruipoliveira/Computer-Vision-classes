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

// Function FindAndDisplayChessboard
// find corners in a cheesboard with board_w x board_h dimensions
// Display the corners in image and return number of detected corners
int FindAndDisplayChessboard(cv::Mat image,int board_w,int board_h, std::vector<cv::Point2f> *corners){

    int board_size = board_w * board_h;
    CvSize board_sz = cvSize(board_w,board_h);

    cv::Mat grey_image;

    cv::cvtColor(image, grey_image, CV_BGR2GRAY);

    // find chessboard corners
    bool found = cv::findChessboardCorners(grey_image, board_sz, *corners,0);

    // Draw results
    if (true){
        cv::drawChessboardCorners(image, board_sz, cv::Mat(*corners), found);
        cv::imshow("Calibration",image);
        //printf("\n Number of corners: %d",corners->size());
        cv::waitKey(0);
    }
    return corners->size();
}


int ex1(){
    // ChessBoard Properties
    int n_boards = 13; //Number of images
    int board_w = 9;
    int board_h = 6;

    int board_sz = board_w * board_h;

    char filename[200];

    // Chessboard coordinates and image pixels
    std::vector<std::vector<cv::Point3f> > object_points;
    std::vector<std::vector<cv::Point2f> > image_points;

    // Corners detected in each image
    std::vector<cv::Point2f> corners;

    int corner_count;

    cv::Mat image;
    int i;

    int sucesses = 0;

    // chessboard coordinates
    std::vector<cv::Point3f> obj;
    for(int j=0;j<board_sz;j++)
    obj.push_back(cv::Point3f(float(j/board_w), float(j%board_w), 0.0));

    for (i=0;i<n_boards;i++){
        // read image
        sprintf(filename,"../images/stereovision/left%02d.jpg",i+1);
        printf("\nReading %s",filename);
        image = cv::imread(filename, CV_LOAD_IMAGE_COLOR);


        if(!image.data){
            printf("\nCould not load image file: %s\n",filename);
            getchar();
            return 0;
        }

        // find and display corners
        corner_count = FindAndDisplayChessboard(image,board_w,board_h,&corners);

        if (corner_count == board_w * board_h){
            image_points.push_back(corners);
            object_points.push_back(obj);
            sucesses++;
        }
    }



    return 0;
}


int ex2(){

  // ChessBoard Properties
    int n_boards = 13; //Number of images
    int board_w = 9;
    int board_h = 6;

    int board_sz = board_w * board_h;

    char filename[200];

    // Chessboard coordinates and image pixels
    std::vector<std::vector<cv::Point3f> > object_points;
    std::vector<std::vector<cv::Point2f> > image_pointsL, image_pointsR ;

    // Corners detected in each image
    std::vector<cv::Point2f> cornersR, cornersL;

    int corner_countL, corner_countR;

    cv::Mat imageL, imageR;
    int i;

    int sucesses = 0;

    // chessboard coordinates
    std::vector<cv::Point3f> obj;
    for(int j=0;j<board_sz;j++)
    obj.push_back(cv::Point3f(float(j/board_w), float(j%board_w), 0.0));



    for (i=0;i<n_boards;i++){
        // read image
        sprintf(filename,"../images/stereovision/left%02d.jpg",i+1);
        printf("\nReading %s",filename);
        imageR = cv::imread(filename, CV_LOAD_IMAGE_COLOR);


        if(!imageR.data){
            printf("\nCould not load image file: %s\n",filename);
            getchar();
            return 0;
        }

        // find and display corners
        corner_countR = FindAndDisplayChessboard(imageR,board_w,board_h,&cornersR);


        sprintf(filename,"../images/stereovision/right%02d.jpg",i+1);
        printf("\nReading %s",filename);
        imageL = cv::imread(filename, CV_LOAD_IMAGE_COLOR);


        if(!imageL.data){
            printf("\nCould not load image file: %s\n",filename);
            getchar();
            return 0;
        }


        corner_countL = FindAndDisplayChessboard(imageL,board_w,board_h,&cornersL);

        if (corner_countL == board_w * board_h){
            image_pointsL.push_back(cornersL);
            object_points.push_back(obj);
            sucesses++;
        }

        if (corner_countR == board_w * board_h){
            image_pointsR.push_back(cornersR);
            //object_pointsR.push_back(obj);
            sucesses++;
        }

    }


    Mat cameraMatrix1, distCoeffs1;
    Mat cameraMatrix2, distCoeffs2;

    Mat R, T, E, F;

    double rms = stereoCalibrate(object_points, image_pointsL, image_pointsR,
            cameraMatrix1, distCoeffs1,
            cameraMatrix2, distCoeffs2,
            imageL.size(), R, T, E, F,
            TermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 50, 1e-6),
            CV_CALIB_FIX_FOCAL_LENGTH );


    cout <<  endl <<"done with RMS error=" << rms << endl;

    cv::FileStorage fs("stereoParams.xml", cv::FileStorage::WRITE);

    if (!fs.isOpened()){
        std::cout << "Failed to open stereoParams.xml" << std::endl;
        return 1;
    }
    else
        std::cout << "Writing camera parameters" << std::endl;
        fs << "cameraMatrix_1" << cameraMatrix1;
        fs << "distCoeffs_1" << distCoeffs1;
        fs << "cameraMatrix_2" << cameraMatrix2;
        fs << "distCoeffs_2" << distCoeffs2;
        fs << "rotation" << R;
        fs << "translation" << T;
        fs << "essential" << E;
        fs << "fundamental" << F;
        fs.release();



    Mat imageUndistortedL;
    for (i=0;i<1;i++){
        // read image
        sprintf(filename,"../images/stereovision/left%02d.jpg",i+1);
        printf("\nReading %s",filename);
        imageL = cv::imread(filename, CV_LOAD_IMAGE_COLOR);


        //imshow("dsad", imageL);

        undistort(imageL, imageUndistortedL, cameraMatrix1, distCoeffs1);



    }
    std::cout << cameraMatrix1 << std::endl;

    imshow("sdada", imageL);
    imshow("undistorted", imageUndistortedL);

    cv::waitKey(-1);


    return 0;
}

int ex3(){
    return 0;
}

int ex4(){
    return 0;

}


int ex5(){

// ChessBoard Properties
    int n_boards = 13; //Number of images
    int board_w = 9;
    int board_h = 6;

    int board_sz = board_w * board_h;

    char filename[200];

    // Chessboard coordinates and image pixels
    std::vector<std::vector<cv::Point3f> > object_points;
    std::vector<std::vector<cv::Point2f> > image_points;

    // Corners detected in each image
    std::vector<cv::Point2f> cornersR, cornersL;

    int corner_countL, corner_countR;

    cv::Mat imageL, imageR;
    int i;

    int sucesses = 0;

    // chessboard coordinates
    std::vector<cv::Point3f> obj;
    for(int j=0;j<board_sz;j++)
    obj.push_back(cv::Point3f(float(j/board_w), float(j%board_w), 0.0));



    for (i=0;i<n_boards;i++){
        // read image
        sprintf(filename,"../images/stereovision/left%02d.jpg",i+1);
        printf("\nReading %s",filename);
        imageR = cv::imread(filename, CV_LOAD_IMAGE_COLOR);


        if(!imageR.data){
            printf("\nCould not load image file: %s\n",filename);
            getchar();
            return 0;
        }

        // find and display corners
        corner_countR = FindAndDisplayChessboard(imageR,board_w,board_h,&cornersR);



        sprintf(filename,"../images/stereovision/right%02d.jpg",i+1);
        printf("\nReading %s",filename);
        imageL = cv::imread(filename, CV_LOAD_IMAGE_COLOR);


        if(!imageL.data){
            printf("\nCould not load image file: %s\n",filename);
            getchar();
            return 0;
        }


        corner_countL = FindAndDisplayChessboard(imageL,board_w,board_h,&cornersL);

        if (corner_countL == board_w * board_h){
            image_points.push_back(cornersL);
            object_points.push_back(obj);
            sucesses++;
        }
    }


    Mat map1x;
    Mat map1y;

    Mat map2x;
    Mat map2y;

    Mat R1;
    Mat R2;

    Mat P1;
    Mat P2;
    Mat Q;

    cout << "\nStereoRectifyMap";
    streoRectify(intrinsics1, distorcion1, intrisincs2, distorcion2, imageL.size(), rotation, translation);

    cout << "\nnewInitUndistorcionMap";
    initUndistorcionRectifyMap(intrisics1, distorcion1, R1 , P1, imageL.size(), CV_32FC1, ...);
    initUndistorcionRectifyMap(intrisics2, distorcion2, R2 , P2, imageR.size(), CV_32FC1, ...);

    cout << "\nRemapMap";
    Mat gray_imagel;
    Mat remap_imagel;
    cvtColor(imageL, gray_imagel, CV_RGB2GRAY);
    remap(gray_imagel, remap_imagel, map1x, map1y, cv::INTER_LINEAR, cv::BORDER_CONSTANT, ...);

    Mat gray_imager;
    Mat remap_imager;
    cvtColor(imageR, gray_imager, CV_RGB2GRAY);
    remap(gray_imager, remap_imager, map2x, map2y, cv::INTER_LINEAR, cv::BORDER_CONSTANT, ...);

    for(int i=0; i<remap_imagel.size().height; i=i+25){
        line(remap_imagel, cvPoint(0,i), cvPoint(remap_imagel.size().width,i), cvScalar(255), 1);
        line(remap_imager, cvPoint(0,i), cvPoint(remap_imager.size().width,i), cvScalar(255), 1);
    }



    imshow("Remap Left",remap_imagel);
    imshow("Remap Right",remap_imager);

    cvWaitKey(-1);

    return 0;


}








