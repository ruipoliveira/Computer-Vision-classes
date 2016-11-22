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


int ex1(){
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

    sprintf(filename,"..//images//stereovision//left%02d.jpg",1);
    cv::Mat  imagel = cv::imread(filename);
    if(!imagel.data){
        printf("\nCould not load image file: %s\n",filename);
        return 0;
    }

    sprintf(filename,"..//images//stereovision//right%02d.jpg",1);
    cv::Mat  imager = cv::imread(filename);
    if(!imager.data){
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
    cv::remap(gray_imagel, remap_imgl, map1x, map1y,cv::INTER_LINEAR);

    cv::Mat  gray_imager;
    cv::Mat  remap_imgr;
    cv::cvtColor(imager, gray_imager , CV_RGB2GRAY);
    cv::remap(gray_imager, remap_imgr, map2x, map2y,cv::INTER_LINEAR);

    /*
    for (int i=0;i<remap_imgl.size().height;i=i+25)
    {
    cv::line(remap_imgl,cvPoint(0,i),cvPoint(remap_imgl.size().width,i),cvScalar(255), 1, 8, 0);
    cv::line(remap_imgr,cvPoint(0,i),cvPoint(remap_imgr.size().width,i),cvScalar(255), 1, 8, 0);
    }
    */

    cv::imshow("Rectify_left",remap_imgl);
    cv::imshow("Rectify_right",remap_imgr);

    //cv::setMouseCallback( "Rectify_left", mouseHandlerL,&remap_imgr);
    //cv::setMouseCallback( "Rectify_right", mouseHandlerR,&remap_imgl);



    // 1- Variable definition
    // the preset has to do with the system configuration (basic, fisheye, etc.)
    // ndisparities is the size of disparity range,
    // in which the optimal disparity at each pixel is searched for.
    // SADWindowSize is the size of averaging window used to match pixel blocks
    // (larger values mean better robustness to noise, but yield blurry disparity maps)
    int ndisparities = 16*5;
    int SADWindowSize = 21;
    cv::Mat imgDisparity8U;
    cv::Mat imgDisparity16S;
    //-- 2. Call the constructor for StereoBM
    //-- 3. Calculate the disparity image

    StereoBM SBM(StereoBM::BASIC_PRESET, ndisparities , SADWindowSize);
    SBM(remap_imgl, remap_imgr, imgDisparity16S, CV_16S);

    //-- Check its extreme values
    double minVal; double maxVal;
    cv::minMaxLoc( imgDisparity16S, &minVal, &maxVal );
    printf("Min disp: %f Max value: %f \n", minVal, maxVal);
    //-- 4. Display it as a CV_8UC1 image
    //Display disparity as a CV_8UC1 image
    // the disparity will be 16-bit signed (fixed-point) or
    //32-bit floating-point image of the same size as left.
    imgDisparity16S.convertTo( imgDisparity8U, CV_8UC1, 255/(maxVal - minVal));
    namedWindow( "disparity", cv::WINDOW_NORMAL );
    cv::imshow( "disparity", imgDisparity8U );

    std::cout << "Rectified images" << std::endl;

        // EXERCICIO 2 - cvReprojectImageTo3D
        Mat points3d;
        reprojectImageTo3D(imgDisparity16S, points3d, Q);

        cv::FileStorage fs2("../points3d.xml", cv::FileStorage::WRITE);
        if (!fs.isOpened()) {
            std::cout << "Failed to open stereoParams.xml" << std::endl;
            return 1;
        }
        fs2 << "points" << points3d;
        fs2.release();



    cv::waitKey(-1);

    return 0;

}



void mouseHandlerL(int event, int x, int y, int flags, void* param){

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


void mouseHandlerR(int event, int x, int y, int flags, void* param){
   switch(event){
   case CV_EVENT_LBUTTONDOWN:
     cv::Mat* image = (cv::Mat*) param;
     std::cout << "pixel coordinates (Left)= " << x << "," << y << std::endl;
     std::vector<cv::Point2f> point;
     cv::line(*image,cvPoint(0,y),cvPoint(image->size().width,y),cvScalar(255), 1, 8, 0);
     cv::imshow("Rectify_left",*image);
    break;
   }
}
