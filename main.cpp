#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int
main (int argc, char** argv)
{
    string mystr;
    int meanK = 50;

    cout << "MeanK(Nothing = 50): ";
    getline (cin,mystr);
    stringstream(mystr) >> meanK;

    float std = 1.0;

    cout << "STD Thresh (Nothing = 1.0): ";
    getline (cin,mystr);
    stringstream(mystr) >> meanK;


    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

    // Fill in the cloud data
    pcl::PCDReader reader;
    // Replace the path below with the path where you saved your file

    char filename[]="Full.pcd";

    reader.read<pcl::PointXYZ> (filename, *cloud);

    std::cerr << "Cloud before filtering: " << std::endl;
    std::cerr << *cloud << std::endl;

    // Create the filtering object
    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
    sor.setInputCloud (cloud);
    sor.setMeanK (meanK);
    sor.setStddevMulThresh (std);
    sor.filter (*cloud_filtered);

    std::cerr << "Cloud after filtering: " << std::endl;
    std::cerr << *cloud_filtered << std::endl;

    pcl::PCDWriter writer;
    writer.write<pcl::PointXYZ> ("inliers.pcd", *cloud_filtered, false);

    sor.setNegative (true);
    sor.filter (*cloud_filtered);
    writer.write<pcl::PointXYZ> ("outliers.pcd", *cloud_filtered, false);

    return (0);
}
