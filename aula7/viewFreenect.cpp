#include <iostream>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

#include <pcl/registration/icp.h>
#include <pcl/filters/voxel_grid.h>

// OpenCV Includes
#include <cv.h>
#include <highgui.h>

using namespace pcl;

void change_color(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud, int r, int g, int b)
{
    //Change colors
    for (int i = 0; i < (*cloud).height * (*cloud).width  ; i++)
      {
        (*cloud).points[i].r = r;
        (*cloud).points[i].g = g;
        (*cloud).points[i].b = b;
      }

}

int  main (int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud1 (new pcl::PointCloud<pcl::PointXYZRGB>);
    PointCloud<PointXYZRGB>::Ptr cloud1_filtered(new PointCloud<PointXYZRGB>);
    
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZRGB>);
    PointCloud<PointXYZRGB>::Ptr cloud2_filtered(new PointCloud<PointXYZRGB>);


    if (pcl::io::loadPCDFile<pcl::PointXYZRGB> ("..//filt_kinect1_cozinha2.pcd", *cloud1) == -1) //* load the file
      {
        PCL_ERROR ("Couldn't read file filt_kinect1_cozinha2.pcd \n");
        return (-1);
      }

    if (pcl::io::loadPCDFile<pcl::PointXYZRGB> ("..//filt_kinect1_cozinha.pcd", *cloud2) == -1) //* load the file
      {
        PCL_ERROR ("Couldn't read file filt_kinect1_cozinha.pcd \n");
        return (-1);
      }
    /*
      // Create the filtering object
      pcl::VoxelGrid<pcl::PointXYZRGB> sor;
      sor.setInputCloud(cloud1);
      sor.setLeafSize(0.01f, 0.01f, 0.01f);
      sor.filter(*cloud1_filtered);
      sor.setInputCloud(cloud2);
      sor.setLeafSize(0.01f, 0.01f, 0.01f);
      sor.filter(*cloud2_filtered);

    */

   pcl::PointCloud<pcl::PointXYZRGB>::Ptr aligned_cloud (new pcl::PointCloud<pcl::PointXYZRGB>);

   pcl::IterativeClosestPoint<pcl::PointXYZRGB, pcl::PointXYZRGB> icp;
   icp.setTransformationEpsilon (1e-6);
   icp.setMaxCorrespondenceDistance (0.25);
   icp.setMaximumIterations (50);

   icp.setInputSource (cloud2);
   icp.setInputTarget (cloud1);

   icp.align (*aligned_cloud);
   //change_color(aligned_cloud,0,0,255);

    //colors cloudAligned red for viewing purposes
    int p = 0;
    for (int i = 0; i < (*aligned_cloud).height; ++i) {
      for (int j = 0; j < (*aligned_cloud).width; j++) {
        (*aligned_cloud).points[p].r = 255;
        (*aligned_cloud).points[p].g = 0;
        (*aligned_cloud).points[p].b = 255;

        p++;
      }
    } 


    visualization::CloudViewer viewer("Simple Cloud Viewer");
    viewer.showCloud(cloud1, "c1");
    viewer.showCloud(cloud2, "c2");
    viewer.showCloud(aligned_cloud, "Aligned");
   //Eigen::Matrix4f transformation = icp.getFinalTransformation ();

  
   while (!viewer.wasStopped())
    {
    }
 
  return (0);
}
