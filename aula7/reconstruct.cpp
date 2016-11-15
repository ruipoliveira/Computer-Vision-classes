#include <iostream>
#include <vector>

#include <stdio.h>
#include <cstdlib>

// OpenCV Includes
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

cv::Mat map1x;
cv::Mat map1y;
cv::Mat map2x;
cv::Mat map2y;

cv::Mat R1;
cv::Mat R2;
cv::Mat P1;
cv::Mat P2;
cv::Mat Q;

/**
 * Final matrixes.
 */
Mat remap_imgl;
Mat remap_imgr;

int main(int argc, char **argv) {
  //int imageToUse = atoi(argv[1]);

  char filename_left[200], filename_right[200];

  cv::Mat image_left_dist, image_right_dist;
  cv::Mat image_left_undist, image_right_undist;

  cv::Mat intrinsic_matrix_1;
  cv::Mat distortion_coeffs_1;
  cv::Mat intrinsic_matrix_2;
  cv::Mat distortion_coeffs_2;
  cv::Mat R, T, E, F;

  // read distortion parameters of the cameras
  cv::FileStorage fs("../stereoParams.xml", cv::FileStorage::READ);
  fs["distCoeffs_1"] >> distortion_coeffs_1;
  fs["distCoeffs_2"] >> distortion_coeffs_2;
  fs["cameraMatrix_1"] >> intrinsic_matrix_1;
  fs["cameraMatrix_2"] >> intrinsic_matrix_2;
  fs["rotation"] >> R;
  fs["translation"] >> T;

  /**
   * select a stereo pair of
   images from the pool of calibration images
   */
  sprintf(filename_left, "..//images//stereovision//left%02d.jpg", 1);
  sprintf(filename_right, "..//images//stereovision//right%02d.jpg", 1);
  image_left_dist = cv::imread(filename_left, CV_LOAD_IMAGE_COLOR);
  image_right_dist = cv::imread(filename_right, CV_LOAD_IMAGE_COLOR);
  cv::undistort(image_left_dist, image_left_undist, intrinsic_matrix_1,
      distortion_coeffs_1);
  cv::undistort(image_right_dist, image_right_undist, intrinsic_matrix_2,
      distortion_coeffs_2);
  //cv::imshow("Left undist", image_left_undist);
  //cv::imshow("Right undist", image_right_undist);

  // stereo rectify
  stereoRectify(intrinsic_matrix_1, distortion_coeffs_1, intrinsic_matrix_2,
      distortion_coeffs_2,
      Size(image_left_undist.cols, image_left_undist.rows), R, T, R1, R2,
      P1, P2, Q);
  // initUndistortRectifyMap
  initUndistortRectifyMap(intrinsic_matrix_1, distortion_coeffs_1, R1, P1,
      Size(image_left_undist.cols, image_left_undist.rows), CV_32FC1,
      map1x, map1y);
  initUndistortRectifyMap(intrinsic_matrix_2, distortion_coeffs_2, R2, P2,
      Size(image_right_undist.cols, image_right_undist.rows), CV_32FC1,
      map2x, map2y);

  // remap
  remap(image_left_undist, remap_imgl, map1x, map1y, INTER_LINEAR);
  remap(image_right_undist, remap_imgr, map2x, map2y, INTER_LINEAR);

  /**
   * Calculate disparity map.
   */
  //Ptr<StereoBM> left_matcher = StereoBM::create();
  // convert to 8UC1
  cvtColor(remap_imgl, remap_imgl, CV_RGB2GRAY);
  cvtColor(remap_imgr, remap_imgr, CV_RGB2GRAY);
  cv::imshow("remap_l", remap_imgl);
  cv::imshow("remap_r", remap_imgr);

  // 1- Variable definition
  // the preset has to do with the system configuration (basic, fisheye, etc.)
  // ndisparities is the size of disparity range,
  // in which the optimal disparity at each pixel is searched for.
  // SADWindowSize is the size of averaging window used to match pixel blocks
  // (larger values mean better robustness to noise, but yield blurry disparity maps)
  int ndisparities = 16 * 5;
  int SADWindowSize = 21;
  cv::Mat imgDisparity8U;
  cv::Mat imgDisparity16S;
  //-- 2. Call the constructor for StereoBM
  /*
  cv::Ptr<cv::StereoBM> sbm;
  sbm = cv::StereoBM::create(ndisparities, SADWindowSize);
  //-- 3. Calculate the disparity image
  sbm->compute(remap_imgl, remap_imgr, imgDisparity16S);//-- Check its extreme values
  */
      StereoBM SBM(StereoBM::BASIC_PRESET, ndisparities , SADWindowSize);
    SBM(remap_imgl, remap_imgr, imgDisparity16S, CV_16S);

  double minVal;
  double maxVal;
  cv::minMaxLoc(imgDisparity16S, &minVal, &maxVal);
  printf("Min disp: %f Max value: %f \n", minVal, maxVal);
  //-- 4. Display it as a CV_8UC1 image
  //Display disparity as a CV_8UC1 image
  // the disparity will be 16-bit signed (fixed-point) or
  //32-bit floating-point image of the same size as left.
  imgDisparity16S.convertTo(imgDisparity8U, CV_8UC1, 255 / (maxVal - minVal));
   cv::imshow("disparity", imgDisparity8U);

  // cvReprojectImageTo3D
  Mat points3d;
  reprojectImageTo3D(imgDisparity16S, points3d, Q);
  // save 3d points in file

  cv::FileStorage fs2("../3dpoints.xml", cv::FileStorage::WRITE);
  if (!fs.isOpened()) {
    std::cout << "Failed to open stereoParams.xml" << std::endl;
    return 1;
  }
  fs2 << "points" << points3d;
  fs2.release();

  cv::waitKey(0);

  return 0;
}