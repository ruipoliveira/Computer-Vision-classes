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


    for (i=0;i<1;i++){
        // read image
        sprintf(filename,"../images/stereovision/left%02d.jpg",i+1);
        printf("\nReading %s",filename);
        imageL = cv::imread(filename, CV_LOAD_IMAGE_COLOR);

    }
    std::cout << cameraMatrix1 << std::endl;

    imshow("sdada", imageL);

    cv::waitKey(-1);


    return 0;
}

int ex3(){

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


void mouseHandlerL4(int event, int x, int y, int flags, void* param)
 {


   switch(event){
     case CV_EVENT_LBUTTONDOWN:
       cv::Mat* image = (cv::Mat*) param;
       std::cout << "pixel coordinates = " << x << "," << y << std::endl;
       std::vector<cv::Point2f> point;
       //cv::line(*image,cvPoint(0,y),cvPoint(image->size().width,y),cvScalar(255), 1, 8, 0);
       //cv::imshow("Rectify_right",*image);
      break;
   }
 }


void mouseHandlerR4(int event, int x, int y, int flags, void* param)
 {
   switch(event){
   case CV_EVENT_LBUTTONDOWN:
     cv::Mat* image = (cv::Mat*) param;
     std::cout << "pixel coordinates = " << x << "," << y << std::endl;
     std::vector<cv::Point2f> point;
     //cv::line(*image,cvPoint(0,y),cvPoint(image->size().width,y),cvScalar(255), 1, 8, 0);
     //cv::imshow("Rectify_left",*image);
    break;
   }
 }

void mouseHandlerL(int event, int x, int y, int flags, void* param)
 {


   switch(event){
     case CV_EVENT_LBUTTONDOWN:
       cv::Mat* image = (cv::Mat*) param;
       std::cout << "pixel coordinates (Left)= " << x << "," << y << std::endl;
       std::vector<cv::Point2f> point;
       cv::line(*image,cvPoint(0,y),cvPoint(image->size().width,y),cvScalar(255), 1, 8, 0);
       cv::imshow("Rectify_right",*image);
      break;
   }
 }


void mouseHandlerR(int event, int x, int y, int flags, void* param)
 {
   switch(event){
   case CV_EVENT_LBUTTONDOWN:
     cv::Mat* image = (cv::Mat*) param;
     std::cout << "pixel coordinates (Right)= " << x << "," << y << std::endl;
     std::vector<cv::Point2f> point;
     cv::line(*image,cvPoint(0,y),cvPoint(image->size().width,y),cvScalar(255), 1, 8, 0);
     cv::imshow("Rectify_left",*image);
    break;
   }
 }


int ex4()
{
  // Read camera parameters
  ///////////////////////
  // Calibrate stereo rig
  //Create first Intrinsic Camera Matrix and Distortion Matrix
  cv::Mat intrinsics1;
  cv::Mat distortion1;

  //Create second Intrinsic Camera Matrix and Distortion Matrix
  cv::Mat intrinsics2;
  cv::Mat distortion2;

  // Calibrate Stereo Rig
  cv::Mat rotation;
  cv::Mat translation;
  cv::Mat essential;
  cv::Mat fundamental;

  // reading parameters
  cv::FileStorage fs("stereoParams.xml", cv::FileStorage::READ);
  if (!fs.isOpened() )
     {
       std::cout << "Failed to open stereoParams.xml" << std::endl;
       return 1;
     }

  fs["cameraMatrix_1"] >>  intrinsics1;
  fs["cameraMatrix_2"] >>  intrinsics2;
  fs["distCoeffs_1"] >>  distortion1;
  fs["distCoeffs_2"] >>  distortion2;
  fs["rotation"] >>  rotation;
  fs["translation"] >>  translation;
  fs["essential"] >>  essential;
  fs["fundamental"] >>  fundamental;

  fs.release();

  char filename[200];

  sprintf(filename,"../images/stereovision/left%02d.jpg",1);
  cv::Mat  imagel = cv::imread(filename);
  if(!imagel.data)
  {
    printf("\nCould not load image file: %s\n",filename);
    return 0;
  }

  sprintf(filename,"../images/stereovision/left%02d.jpg",1);
  cv::Mat  imager = cv::imread(filename);
  if(!imager.data)
  {
    printf("\nCould not load image file: %s\n",filename);
    return 0;
  }

  cv::Mat map1x;
  cv::Mat map1y;
  cv::Mat map2x;
  cv::Mat map2y;

  cv::Mat R1;
  cv::Mat R2;

  cv::Mat P1;
  cv::Mat P2;
  cv::Mat Q;

  std::cout << "\nStereoRectifyMap";
  cv::stereoRectify(intrinsics1, distortion1, intrinsics2, distortion2, imagel.size(), rotation, translation,R1, R2, P1, P2, Q,0);

  std::cout << "\ncvInitUndistortRectifyMap";
  cv::initUndistortRectifyMap(intrinsics1, distortion1, R1, P1, imagel.size(), CV_32FC1, map1x, map1y);
  cv::initUndistortRectifyMap(intrinsics2, distortion2, R2, P2, imagel.size(), CV_32FC1, map2x,map2y);

  std::cout << "\nRemap images";
  cv::Mat  gray_imagel;
  cv::Mat  remap_imgl;
  cv::cvtColor(imagel, gray_imagel , CV_RGB2GRAY);
  cv::remap(gray_imagel, remap_imgl, map1x, map1y,cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

  cv::Mat  gray_imager;
  cv::Mat  remap_imgr;
  cv::cvtColor(imager, gray_imager , CV_RGB2GRAY);
  cv::remap(gray_imager, remap_imgr, map2x, map2y,cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());


  cv::imshow("Callback",remap_imgr);
  cv::setMouseCallback( "Callback", mouseHandlerL4,&remap_imgl);

  std::cout << "Rectified images" << std::endl;
  cv::waitKey(-1);

  return 0;
  }

int ex5()
{
  // Read camera parameters
  ///////////////////////
  // Calibrate stereo rig
  //Create first Intrinsic Camera Matrix and Distortion Matrix
  cv::Mat intrinsics1;
  cv::Mat distortion1;

  //Create second Intrinsic Camera Matrix and Distortion Matrix
  cv::Mat intrinsics2;
  cv::Mat distortion2;

  // Calibrate Stereo Rig
  cv::Mat rotation;
  cv::Mat translation;
  cv::Mat essential;
  cv::Mat fundamental;

  // reading parameters
  cv::FileStorage fs("stereoParams.xml", cv::FileStorage::READ);
  if (!fs.isOpened() )
     {
       std::cout << "Failed to open stereoParams.xml" << std::endl;
       return 1;
     }

  fs["cameraMatrix_1"] >>  intrinsics1;
  fs["cameraMatrix_2"] >>  intrinsics2;
  fs["distCoeffs_1"] >>  distortion1;
  fs["distCoeffs_2"] >>  distortion2;
  fs["rotation"] >>  rotation;
  fs["translation"] >>  translation;
  fs["essential"] >>  essential;
  fs["fundamental"] >>  fundamental;

  fs.release();

  char filename[200];

  sprintf(filename,"../images/stereovision/left%02d.jpg",1);
  cv::Mat  imagel = cv::imread(filename);
  if(!imagel.data)
  {
    printf("\nCould not load image file: %s\n",filename);
    return 0;
  }

  sprintf(filename,"../images/stereovision/left%02d.jpg",1);
  cv::Mat  imager = cv::imread(filename);
  if(!imager.data)
  {
    printf("\nCould not load image file: %s\n",filename);
    return 0;
  }

  cv::Mat map1x;
  cv::Mat map1y;
  cv::Mat map2x;
  cv::Mat map2y;

  cv::Mat R1;
  cv::Mat R2;

  cv::Mat P1;
  cv::Mat P2;
  cv::Mat Q;

  std::cout << "\nStereoRectifyMap";
  cv::stereoRectify(intrinsics1, distortion1, intrinsics2, distortion2, imagel.size(), rotation, translation,R1, R2, P1, P2, Q,0);

  std::cout << "\ncvInitUndistortRectifyMap";
  cv::initUndistortRectifyMap(intrinsics1, distortion1, R1, P1, imagel.size(), CV_32FC1, map1x, map1y);
  cv::initUndistortRectifyMap(intrinsics2, distortion2, R2, P2, imagel.size(), CV_32FC1, map2x,map2y);

  std::cout << "\nRemap images";
  cv::Mat  gray_imagel;
  cv::Mat  remap_imgl;
  cv::cvtColor(imagel, gray_imagel , CV_RGB2GRAY);
  cv::remap(gray_imagel, remap_imgl, map1x, map1y,cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

  cv::Mat  gray_imager;
  cv::Mat  remap_imgr;
  cv::cvtColor(imager, gray_imager , CV_RGB2GRAY);
  cv::remap(gray_imager, remap_imgr, map2x, map2y,cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

  for (int i=0;i<remap_imgl.size().height;i=i+25)
  {
    cv::line(remap_imgl,cvPoint(0,i),cvPoint(remap_imgl.size().width,i),cvScalar(255), 1, 8, 0);
    cv::line(remap_imgr,cvPoint(0,i),cvPoint(remap_imgr.size().width,i),cvScalar(255), 1, 8, 0);
  }

  cv::imshow("Rectify_left",remap_imgl);
  cv::imshow("Rectify_right",remap_imgr);

  cv::setMouseCallback( "Rectify_left", mouseHandlerL,&remap_imgr);
  cv::setMouseCallback( "Rectify_right", mouseHandlerR,&remap_imgl);

  std::cout << "Rectified images" << std::endl;
  cv::waitKey(-1);

  return 0;
  }








