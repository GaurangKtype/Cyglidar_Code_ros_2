#ifndef __D1_2D_TOPIC_H
#define __D1_2D_TOPIC_H

#include "d_series_constant.h"
#include "cyglidar_driver.h"
#include "serial.h"

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/point_cloud.h>

class Topic2D
{
    public:
        void initPublisher(ros::Publisher _publisher_laserscan, ros::Publisher _publisher_point_2d);

        void assignLaserScan(std::string _frame_id);
        void publishScanLaser(ros::Time _start_time, uint16_t *_distance_buffer_2d);

        void assignPCL2D(std::string _frame_id);
        void mappingPointCloud2D(uint16_t *_distance_buffer_2d);
        void publishPoint2D(uint16_t *_distance_buffer_2d);

    private:
        ros::Publisher publisher_laserscan;
        ros::Publisher publisher_point_2d;
        sensor_msgs::LaserScan message_laserscan;
        pcl::PointCloud<pcl::PointXYZRGBA> pcl_2d;

        uint8_t buffer_index;
        uint16_t raw_distance;
        const float angle_increment_steps = Constant_D1::Sensor::AngleIncremet2D;
        float camera_coordinate_x, camera_coordinate_y;

};

#endif
