#include "ex4.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;

int show2images() {

double alpha = 0.5; double beta; double input;

 Mat src1, src2, dst;

 /// Ask the user enter alpha
 std::cout<<" Simple Linear Blender "<<std::endl;
 std::cout<<"-----------------------"<<std::endl;
 std::cout<<"* Enter alpha [0-1]: ";
 std::cin>>input;

 /// We use the alpha provided by the user if it is between 0 and 1
 if( input >= 0.0 && input <= 1.0 )
   { alpha = input; }

 /// imagens com mesmas dimensoes
 src1 = imread("../images/lena.jpg");
 src2 = imread("../images/lena_bin.jpg");

 if( !src1.data ) {  return -1; }
 if( !src2.data ) {  return -1; }

 /// Create Windows
 namedWindow("Linear Blend", 1);

 beta = ( 1.0 - alpha );
 addWeighted( src1, alpha, src2, beta, 0.0, dst);

 imshow( "Linear Blend", dst );

 waitKey(0);



/*
    Mat img1 = imread("../images/lena.jpg", CV_LOAD_IMAGE_COLOR);
    Mat img2 = imread("../images/deti.jpg", CV_LOAD_IMAGE_COLOR);

    if(img1.empty() || img2.empty())
       return -1;

    namedWindow( "lena", CV_WINDOW_AUTOSIZE);
    imshow("lena", img1);

    namedWindow( "deti", CV_WINDOW_AUTOSIZE);
    imshow("deti", img2);

    waitKey(0);
*/
}

int to_Gray() {

    Mat gray_image;
    Mat img = imread("../images/lena.jpg", CV_LOAD_IMAGE_COLOR);

    if(img.empty())
       return -1;

    cvtColor( img, gray_image, CV_BGR2GRAY );

    namedWindow( "lena", CV_WINDOW_AUTOSIZE);
    imshow("lena_cinza", gray_image);

    waitKey(0);

}

int to_YUV() {

    Mat yuv_image;
    Mat img = imread("../images/lena.jpg", CV_LOAD_IMAGE_COLOR);

    if(img.empty())
       return -1;

    cvtColor( img, yuv_image, CV_BGR2YUV );

    namedWindow( "lena", CV_WINDOW_AUTOSIZE);
    imshow("lena_yuv", yuv_image);

    waitKey(0);

}

int modifyAndSave(){

    Mat img = imread("../images/lena.jpg", CV_LOAD_IMAGE_COLOR);

    if(img.empty())
       return -1;

    cvtColor( img, img, CV_BGR2GRAY );

    threshold(img, img, 100, 255, THRESH_BINARY);

    imwrite( "../images/lena_bin.jpg", img );

    imshow("lena_bin", img);

    waitKey(0);
}

