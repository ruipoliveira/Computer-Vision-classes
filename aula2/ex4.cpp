#include "ex4.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int show2images() {

    Mat img1 = imread("../images/lena.jpg", CV_LOAD_IMAGE_COLOR);
    Mat img2 = imread("../images/deti.jpg", CV_LOAD_IMAGE_COLOR);

    if(img1.empty() || img2.empty())
       return -1;

    namedWindow( "lena", CV_WINDOW_AUTOSIZE);
    imshow("lena", img1);

    namedWindow( "deti", CV_WINDOW_AUTOSIZE);
    imshow("deti", img2);

    waitKey(0);

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

