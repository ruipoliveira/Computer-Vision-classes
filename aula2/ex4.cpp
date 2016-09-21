#include "ex4.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


int MyFunc() {

    Mat gray_image;
    Mat img = imread("../images/lena.jpg", CV_LOAD_IMAGE_COLOR);

    if(img.empty())
       return -1;

    cvtColor( img, gray_image, CV_BGR2GRAY );

    namedWindow( "lena", CV_WINDOW_AUTOSIZE);
    imshow("lena", gray_image);

    waitKey(0);

}
