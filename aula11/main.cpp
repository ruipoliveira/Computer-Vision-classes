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


int main(int argc, char **argv){
    int val_return;

    //val_return = ex1_1();
    //val_return = ex1_2();
    //val_return = ex2_SIFT_AND_FAST();
    //val_return = ex2_SURF1();
    val_return = ex2_SURF2();

    return val_return;

}



