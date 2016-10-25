#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int FindAndDisplayChessboard(cv::Mat image,int board_w,int board_h, std::vector<cv::Point2f> *corners);
int ex1();
int ex2();
int ex3();
int ex4();
