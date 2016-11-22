#include "ex4.h"

ex4::ex4()
{
    Mat img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if(img.empty())
       return -1;
    namedWindow( "lena", CV_WINDOW_AUTOSIZE );
    imshow("lena", img);
    waitKey(0);
    return 0;

    //ctor
}

ex4::~ex4()
{
    //dtor
}
