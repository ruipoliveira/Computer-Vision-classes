#include "fileSource.h"
#include <iostream>
#include <vector>

// OpenCV Includes
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
        printf("\n Number of corners: %d",corners->size());
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

    //dicas guiao
    cv::Mat intrinsic = cv::Mat(3, 3, CV_32FC1);
    cv::Mat distCoeffs;
    std::vector<cv::Mat> rvecs;
    std::vector<cv::Mat> tvecs;

    // Chessboard coordinates and image pixels
    std::vector<std::vector<cv::Point3f> > object_points;
    std::vector<std::vector<cv::Point2f> > image_points;

    // Corners detected in each image
    std::vector<cv::Point2f> corners;
    int corner_count;
    cv::Mat image;
    int i, sucesses,flags = 0;

    // chessboard coordinates
    std::vector<cv::Point3f> obj;
    for(int j=0;j<board_sz;j++)
    obj.push_back(cv::Point3f(float(j/board_w), float(j%board_w), 0.0));

    for (i=0;i<n_boards;i++){
        // read image
        sprintf(filename,"../aula5-resources/images//left%02d.jpg",i+1);
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

    CvTermCriteria term_crit=cvTermCriteria( CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,30,DBL_EPSILON);
    calibrateCamera(object_points, image_points, image.size(), intrinsic, distCoeffs, rvecs, tvecs);

    std::cout << std::endl << "Intrinsics = "<< std::endl << " " << intrinsic << std::endl
    << std::endl;
    std::cout << std::endl << "Distortion = "<< std::endl << " " << distCoeffs << std::endl
    << std::endl;
    std::cout << std::endl << "Translations = "<< std::endl ;
    for (i=0;i<n_boards;i++)
    std::cout << std::endl << tvecs.at(i);
    std::cout << std::endl << "Rotations= "<< std::endl ;
    for (i=0;i<n_boards;i++)
    std::cout << std::endl << rvecs.at(i);

    cv::FileStorage fs("../CamParams.xml", cv::FileStorage::WRITE);
    fs << "cameraMatrix" << intrinsic << "distCoeffs" << distCoeffs;
    fs.release();

    return 0;
}


int ex2(){
    // ChessBoard Properties
    int n_boards = 13; //Number of images
    int board_w = 9;
    int board_h = 6;

    int board_sz = board_w * board_h;

    char filename[200];

    //dicas guiao
    cv::Mat intrinsic = cv::Mat(3, 3, CV_32FC1);
    cv::Mat distCoeffs;
    std::vector<cv::Mat> rvecs;
    std::vector<cv::Mat> tvecs;

    // Chessboard coordinates and image pixels
    std::vector<std::vector<cv::Point3f> > object_points;
    std::vector<std::vector<cv::Point2f> > image_points;

    // Corners detected in each image
    std::vector<cv::Point2f> corners;

    int corner_count;

    cv::Mat image;
    int i;

    int sucesses,flags = 0;


    // chessboard coordinates
    std::vector<cv::Point3f> obj;
    for(int j=0;j<board_sz;j++)
    obj.push_back(cv::Point3f(float(j/board_w), float(j%board_w), 0.0));

    for (i=0;i<n_boards;i++){
        // read image
        sprintf(filename,"../aula5-resources/images//left%02d.jpg",i+1);
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


    //cenas adicionais
    CvTermCriteria term_crit=cvTermCriteria( CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,30,DBL_EPSILON);
    calibrateCamera(object_points, image_points, image.size(), intrinsic, distCoeffs, rvecs, tvecs);

    //guiao
    std::cout << std::endl << "Intrinsics = "<< std::endl << " " << intrinsic << std::endl
    << std::endl;
    std::cout << std::endl << "Distortion = "<< std::endl << " " << distCoeffs << std::endl
    << std::endl;
    std::cout << std::endl << "Translations = "<< std::endl ;
    for (i=0;i<n_boards;i++)
    std::cout << std::endl << tvecs.at(i);
    std::cout << std::endl << "Rotations= "<< std::endl ;
    for (i=0;i<n_boards;i++)
    std::cout << std::endl << rvecs.at(i);

    cv::FileStorage fs("../CamParams.xml", cv::FileStorage::WRITE);
    fs << "cameraMatrix" << intrinsic << "distCoeffs" << distCoeffs;
    fs.release();

    // Cubo
    std::vector<Point3f> new_object_points;
    new_object_points.push_back(Point3f(0.0, 0.0, 0.0)); // vertice0
    new_object_points.push_back(Point3f(0.0, 0.0, 1.0)); // vertice1
    new_object_points.push_back(Point3f(1.0, 0.0, 0.0)); // vertice2
    new_object_points.push_back(Point3f(1.0, 0.0, 1.0)); // vertice3
    new_object_points.push_back(Point3f(0.0, 1.0, 0.0)); // vertice4
    new_object_points.push_back(Point3f(0.0, 1.0, 1.0)); // vertice5
    new_object_points.push_back(Point3f(1.0, 1.0, 0.0)); // vertice6
    new_object_points.push_back(Point3f(1.0, 1.0, 1.0)); // vertice7

    for (i = 0; i < n_boards; i++){
        // read image
        sprintf(filename, "../aula5-resources/images//left%02d.jpg", i + 1);
        printf("\nReading %s", filename);
        image = imread(filename, CV_LOAD_IMAGE_COLOR);


        if (!image.data){
            printf("\nCould not load image file: %s\n", filename);
            getchar();
            return 0;
        }

        std::vector<cv::Point2f> projected_points;
        projectPoints(new_object_points, rvecs.at(i), tvecs.at(i), intrinsic, distCoeffs, projected_points);

        //desenhar cubo 0,255,255 cor amarela
        line(image, projected_points[0], projected_points[1], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[0], projected_points[2], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[0], projected_points[4], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[1], projected_points[3], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[1], projected_points[5], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[2], projected_points[3], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[2], projected_points[6], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[3], projected_points[7], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[4], projected_points[5], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[4], projected_points[6], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[5], projected_points[7], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[6], projected_points[7], Scalar(0, 255, 255), 2, 8);
        imshow("Calibration", image);
        waitKey(0);
    }

    return 0;
}

int ex3(){
    // ChessBoard Properties
    int n_boards = 14; //Number of images
    int board_w = 9;
    int board_h = 6;

    int board_sz = board_w * board_h;

    char filename[200];

    cv::Mat image, image_gray;
    cv::VideoCapture cap(0); // open the video camera no. 0

    // Access Video
    if (!cap.isOpened()){
        std::cout << "Cannot open the video file" << std::endl;
        getchar();
        return -1;
    }

    int k=0;

    while (true){
        cap >> image;

        cvtColor(image,image_gray,CV_BGR2GRAY);
        int key = waitKey(10);

        imshow("cam", image);
        if (key == 32){
            sprintf(filename,"../aula5-resources/images//nossasimagens%02d.jpg",k+1);
            std::cout << "Write image #" << k+1 << std::endl;
            imwrite(filename, image_gray );
            k++;
        }
        if (k== n_boards) break;
    }


    //dicas guiao
    cv::Mat intrinsic = cv::Mat(3, 3, CV_32FC1);
    cv::Mat distCoeffs;
    std::vector<cv::Mat> rvecs;
    std::vector<cv::Mat> tvecs;

    // Chessboard coordinates and image pixels
    std::vector<std::vector<cv::Point3f> > object_points;
    std::vector<std::vector<cv::Point2f> > image_points;

    // Corners detected in each image
    std::vector<cv::Point2f> corners;

    int corner_count, i,sucesses,flags = 0;

    // chessboard coordinates
    std::vector<cv::Point3f> obj;
    for(int j=0;j<board_sz;j++)
    obj.push_back(cv::Point3f(float(j/board_w), float(j%board_w), 0.0));

    for (i=0;i<n_boards;i++){
        // read image
        if(i<13){
            sprintf(filename,"../aula5-resources/images//nossasimagens%02d.jpg",i+2);
            printf("\nReading %s",filename);
            image = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
        }
        else continue;

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

    //cenas adicionais
    CvTermCriteria term_crit=cvTermCriteria( CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,30,DBL_EPSILON);
    calibrateCamera(object_points, image_points, image.size(), intrinsic, distCoeffs, rvecs, tvecs);

    //guiao
    std::cout << std::endl << "Intrinsics = "<< std::endl << " " << intrinsic << std::endl
    << std::endl;
    std::cout << std::endl << "Distortion = "<< std::endl << " " << distCoeffs << std::endl
    << std::endl;
    std::cout << std::endl << "Translations = "<< std::endl ;
    for (i=0;i<n_boards-1;i++)
    std::cout << std::endl << tvecs.at(i);
    std::cout << std::endl << "Rotations= "<< std::endl ;
    for (i=0;i<n_boards-1;i++)
    std::cout << std::endl << rvecs.at(i);

    cv::FileStorage fs("../CamParams.xml", cv::FileStorage::WRITE);
    fs << "cameraMatrix" << intrinsic << "distCoeffs" << distCoeffs;
    fs.release();

    // Cubo
    std::vector<Point3f> new_object_points;
    new_object_points.push_back(Point3f(0.0, 0.0, 0.0)); // vertice0
    new_object_points.push_back(Point3f(0.0, 0.0, 1.0)); // vertice1
    new_object_points.push_back(Point3f(1.0, 0.0, 0.0)); // vertice2
    new_object_points.push_back(Point3f(1.0, 0.0, 1.0)); // vertice3
    new_object_points.push_back(Point3f(0.0, 1.0, 0.0)); // vertice4
    new_object_points.push_back(Point3f(0.0, 1.0, 1.0)); // vertice5
    new_object_points.push_back(Point3f(1.0, 1.0, 0.0)); // vertice6
    new_object_points.push_back(Point3f(1.0, 1.0, 1.0)); // vertice7

    for (i = 1; i < n_boards; i++){
    // read image
        sprintf(filename, "../aula5-resources/images//nossasimagens%02d.jpg", i+1);
        printf("\nReading %s", filename);
        image = imread(filename, CV_LOAD_IMAGE_COLOR);


        if (!image.data){
            printf("\nCould not load image file: %s\n", filename);
            getchar();
            return 0;
        }

        std::vector<cv::Point2f> projected_points;
        projectPoints(new_object_points, rvecs.at(i), tvecs.at(i), intrinsic, distCoeffs, projected_points);

        //desenhar cubo 0,255,255 cor amarela
        line(image, projected_points[0], projected_points[1], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[0], projected_points[2], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[0], projected_points[4], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[1], projected_points[3], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[1], projected_points[5], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[2], projected_points[3], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[2], projected_points[6], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[3], projected_points[7], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[4], projected_points[5], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[4], projected_points[6], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[5], projected_points[7], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[6], projected_points[7], Scalar(0, 255, 255), 2, 8);

        imshow("Calibration", image);

        waitKey(0);
    }

    return 0;
}

int ex4(){


    cv::FileStorage fs("../CamParams.xml", cv::FileStorage::READ);
    cv::Mat intrinsic = cv::Mat(3, 3, CV_32FC1);
    cv::Mat distCoeffs;
    fs["cameraMatrix"] >> intrinsic;
    fs["distCoeffs"] >> distCoeffs;

  // ChessBoard Properties
    int n_boards = 14; //Number of images
    int board_w = 9;

    int board_h = 6;

    int board_sz = board_w * board_h;

    char filename[200];

    cv::Mat image, image_gray;
    cv::VideoCapture cap(0); // open the video camera no. 0

    // Access Video
    if (!cap.isOpened()){
        std::cout << "Cannot open the video file" << std::endl;
        getchar();
        return -1;
    }

    int k=0;

    std::vector<cv::Point3f> objectPoints, cubePoints;
    cubePoints.push_back(cv::Point3f(0.0, 0.0, 0.0));
    cubePoints.push_back(cv::Point3f(0.0, 1.0, 0.0));
    cubePoints.push_back(cv::Point3f(1.0, 0.0, 0.0));
    cubePoints.push_back(cv::Point3f(1.0, 1.0, 0.0));
    cubePoints.push_back(cv::Point3f(0.0, 0.0, -1.0));
    cubePoints.push_back(cv::Point3f(0.0, 1.0, -1.0));
    cubePoints.push_back(cv::Point3f(1.0, 0.0, -1.0));
    cubePoints.push_back(cv::Point3f(1.0, 1.0, -1.0));

    int board_size = board_w * board_h;


    for (int i = 0; i < board_h; i++)
    for (int j = 0; j < board_w; j++)
    objectPoints.push_back(cv::Point3f((float)j,(float)i, 0.0));

    int i = 0;
    VideoCapture capture(0);

    int sucesses = 0;

    if (!cap.isOpened()){
        std::cout << "Cannot open the video file" << std::endl;
        getchar();
        return -1;
    }

    while (true){
        cap >> image; // get a new frame from camera
        desenharCubo(&image, board_w, board_h,  &intrinsic, &distCoeffs, &cubePoints, &objectPoints);
        imshow("cam", image);

        if(cv::waitKey(30) >= 0) break;
    }

    cv::Mat grey_image;
while (true){
        cap >> image;

        cvtColor(image,image_gray,CV_BGR2GRAY);
        int key = waitKey(10);

}
}


void desenharCubo(cv::Mat *image, int board_w,int board_h, cv::Mat *intrinsic, cv::Mat *distCoeffs,
                    std::vector<cv::Point3f> *cubePoints,std::vector<cv::Point3f> *objectPoints){

    int board_size = board_w * board_h;
    CvSize board_sz = cvSize(board_w,board_h);

    cv::Mat grey_image;

    cv::cvtColor(*image, grey_image, CV_BGR2GRAY);

    cv::Mat rvec(3,1,cv::DataType<double>::type);
    cv::Mat tvec(3,1,cv::DataType<double>::type);

    std::vector<cv::Point2f> corners;

    bool found = cv::findChessboardCorners(grey_image, board_sz, corners, 0);
    if (!found)
    return;

    cv::solvePnP(*objectPoints, corners, *intrinsic, *distCoeffs, rvec, tvec, false);
    std::vector<cv::Point2f> imagePoints;
    cv::projectPoints(*cubePoints, rvec, tvec, *intrinsic, *distCoeffs, imagePoints);

    // Draw results
    line(*image, imagePoints[0], imagePoints[1], cv::Scalar( 0, 255, 0 ), 2);
    line(*image, imagePoints[0], imagePoints[2], cv::Scalar( 0, 255, 0 ), 2);
    line(*image, imagePoints[1], imagePoints[3], cv::Scalar( 0, 255, 0 ), 2);
    line(*image, imagePoints[2], imagePoints[3], cv::Scalar( 0, 255, 0 ), 2);

    line(*image, imagePoints[4], imagePoints[5], cv::Scalar( 0, 255, 0 ), 2);
    line(*image, imagePoints[4], imagePoints[6], cv::Scalar( 0, 255, 0 ), 2);
    line(*image, imagePoints[5], imagePoints[7], cv::Scalar( 0, 255, 0 ), 2);
    line(*image, imagePoints[6], imagePoints[7], cv::Scalar( 0, 255, 0 ), 2);

    line(*image, imagePoints[0], imagePoints[4], cv::Scalar( 0, 255, 0 ), 2);
    line(*image, imagePoints[1], imagePoints[5], cv::Scalar( 0, 255, 0 ), 2);
    line(*image, imagePoints[2], imagePoints[6], cv::Scalar( 0, 255, 0 ), 2);
    line(*image, imagePoints[3], imagePoints[7], cv::Scalar( 0, 255, 0 ), 2);

        imshow("cam", image);
        if (key == 32){
            sprintf(filename,"../aula5-resources/images//nossasimagens%02d.jpg",k+1);
            std::cout << "Write image #" << k+1 << std::endl;
            imwrite(filename, image_gray );
            k++;
        }
        if (k== n_boards) break;
    }


    std::vector<cv::Mat> rvecs;
    std::vector<cv::Mat> tvecs;

    // Chessboard coordinates and image pixels
    std::vector<std::vector<cv::Point3f> > object_points;
    std::vector<std::vector<cv::Point2f> > image_points;

    // Corners detected in each image
    std::vector<cv::Point2f> corners;

    int corner_count, i,sucesses,flags = 0;

    // chessboard coordinates
    std::vector<cv::Point3f> obj;
    for(int j=0;j<board_sz;j++)
    obj.push_back(cv::Point3f(float(j/board_w), float(j%board_w), 0.0));

    for (i=0;i<n_boards;i++){
        // read image
        if(i<13){
            sprintf(filename,"../aula5-resources/images//nossasimagens%02d.jpg",i+2);
            printf("\nReading %s",filename);
            image = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
        }
        else continue;

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

    //cenas adicionais
    CvTermCriteria term_crit=cvTermCriteria( CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,30,DBL_EPSILON);
    calibrateCamera(object_points, image_points, image.size(), intrinsic, distCoeffs, rvecs, tvecs);

    //guiao
    std::cout << std::endl << "Intrinsics = "<< std::endl << " " << intrinsic << std::endl
    << std::endl;
    std::cout << std::endl << "Distortion = "<< std::endl << " " << distCoeffs << std::endl
    << std::endl;
    std::cout << std::endl << "Translations = "<< std::endl ;
    for (i=0;i<n_boards-1;i++)
    std::cout << std::endl << tvecs.at(i);
    std::cout << std::endl << "Rotations= "<< std::endl ;
    for (i=0;i<n_boards-1;i++)
    std::cout << std::endl << rvecs.at(i);

    // Cubo
    std::vector<Point3f> new_object_points;
    new_object_points.push_back(Point3f(0.0, 0.0, 0.0)); // vertice0
    new_object_points.push_back(Point3f(0.0, 0.0, 1.0)); // vertice1
    new_object_points.push_back(Point3f(1.0, 0.0, 0.0)); // vertice2
    new_object_points.push_back(Point3f(1.0, 0.0, 1.0)); // vertice3
    new_object_points.push_back(Point3f(0.0, 1.0, 0.0)); // vertice4
    new_object_points.push_back(Point3f(0.0, 1.0, 1.0)); // vertice5
    new_object_points.push_back(Point3f(1.0, 1.0, 0.0)); // vertice6
    new_object_points.push_back(Point3f(1.0, 1.0, 1.0)); // vertice7

    for (i = 1; i < n_boards; i++){
    // read image
        sprintf(filename, "../aula5-resources/images//nossasimagens%02d.jpg", i+1);
        printf("\nReading %s", filename);
        image = imread(filename, CV_LOAD_IMAGE_COLOR);


        if (!image.data){
            printf("\nCould not load image file: %s\n", filename);
            getchar();
            return 0;
        }

        solvePnP(obj, corners, intrinsic, distCoeffs, rvecs, tvecs);
        std::vector<cv::Point2f> projected_points;
        projectPoints(new_object_points, rvecs.at(i), tvecs.at(i), intrinsic, distCoeffs, projected_points);

        //desenhar cubo 0,255,255 cor amarela
        line(image, projected_points[0], projected_points[1], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[0], projected_points[2], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[0], projected_points[4], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[1], projected_points[3], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[1], projected_points[5], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[2], projected_points[3], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[2], projected_points[6], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[3], projected_points[7], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[4], projected_points[5], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[4], projected_points[6], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[5], projected_points[7], Scalar(0, 255, 255), 2, 8);
        line(image, projected_points[6], projected_points[7], Scalar(0, 255, 255), 2, 8);

        imshow("Calibration", image);

        waitKey(0);
    }

    return 0;

}









