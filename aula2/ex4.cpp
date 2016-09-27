#include "ex4.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;


/*
* Exercício 4 converter para binário
*/
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

/*
* Exercício 4 converter para gray
*/
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

/*
* Exercício 4 converter para YUV
*/

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


/*
* Exercício 5
*/
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


}



/*
* Exercicio 6
* http://docs.opencv.org/2.4/doc/tutorials/core/basic_linear_transform/basic_linear_transform.html
*/
int contrastAndBrightness(){

    double alpha; /**< Simple contrast control */
    int beta;  /**< Simple brightness control */

    Mat img = imread("../images/lena.jpg", CV_LOAD_IMAGE_COLOR);

    Mat new_image = Mat::zeros( img.size(), img.type() );

    std::cout<<" Basic Linear Transforms "<<std::endl;
    std::cout<<"-------------------------"<<std::endl;
    std::cout<<"* Enter the alpha value [1.0-3.0]: ";std::cin>>alpha;
    std::cout<<"* Enter the beta value [0-100]: "; std::cin>>beta;

    /// Do the operation new_image(i,j) = alpha*image(i,j) + beta
    for( int y = 0; y < img.rows; y++ ){
        for( int x = 0; x < img.cols; x++ ){
            for( int c = 0; c < 3; c++ ){
                new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha*( img.at<Vec3b>(y,x)[c] ) + beta );
            }
        }
    }

    namedWindow("Original Image", 1);
    namedWindow("New Image", 1);

    /// Show stuff
    imshow("Original Image", img);
    imshow("New Image", new_image);

    waitKey();

}



/*
* Exercicio 7
* http://www.swarthmore.edu/NatSci/mzucker1/opencv-2.4.10-docs/doc/tutorials/core/how_to_scan_images/how_to_scan_images.html#howtoscanimagesopencv
*/

//Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
//{
//    // accept only char type matrices
//    CV_Assert(I.depth() != sizeof(uchar));
//
//    const int channels = I.channels();
//    switch(channels)
//    {
//    case 1:
//        {
//            MatIterator_<uchar> it, end;
//            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
//                *it = table[*it];
//            break;
//        }
//    case 3:
//        {
//            MatIterator_<Vec3b> it, end;
//            for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
//            {
//                (*it)[0] = table[(*it)[0]];
//                (*it)[1] = table[(*it)[1]];
//                (*it)[2] = table[(*it)[2]];
//            }
//        }
//    }
//
//    return I;
//}
