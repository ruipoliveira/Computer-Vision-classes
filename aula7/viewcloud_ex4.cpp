
#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/pcd_io.h>

#include <pcl/point_types.h>
#include <opencv2/opencv.hpp>


using namespace pcl;


int  main (int argc, char** argv){

  PointCloud<PointXYZRGB>::Ptr cloud1(new PointCloud<PointXYZRGB>);
  PointCloud<PointXYZRGB>::Ptr cloud2(new PointCloud<PointXYZRGB>);


  if (io::loadPCDFile<pcl::PointXYZRGB>("../filt_office1.pcd", *cloud1) == -1) {
    PCL_ERROR("Couldn't read file filt_office1.pcd \n");
    return (-1);
  }

  if (io::loadPCDFile<pcl::PointXYZRGB>("../filt_office2.pcd", *cloud2) == -1) {
    PCL_ERROR("Couldn't read file filt_office2.pcd \n");
    return (-1);
  }

  pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
  
  viewer.showCloud(cloud2, "cloud2");
  
  viewer.showCloud(cloud1, "cloud1");

  while (!viewer.wasStopped()) {
  }

}