#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Odometry.h>
int main(int argc, char** argv)
{
    ros::init(argc, argv, "read_bag_file");
    ros::NodeHandle nh;
    ros::Rate loop_rate(100);
}
rosbag::Bag bag;
bag.open("hello.bag", rosbag::bagmode::Read);

std::vector<std::string> topics;
topics.push_back(std::string("/imu_topic")); // IMU的话题名称
topics.push_back(std::string("/odom_topic")); // odometry的话题名称

rosbag::View view(bag, rosbag::TopicQuery(topics));
for(rosbag::MessageInstance const& m : view)
{
    if(m.getTopic() == "/imu_topic")
    {
        sensor_msgs::Imu::ConstPtr imu = m.instantiate<sensor_msgs::Imu>();
        if(imu != NULL)
        {
            // 使用IMU数据的代码
            std::cout << "seq: " << imu->header.seq << "\n";
            std::cout << "x_acc: " << imu->linear_acceleration.x << "\n";
            std::cout << "y_acc: " << imu->linear_acceleration.y << "\n";
            std::cout << "z_acc: " << imu->linear_acceleration.z << "\n";
        }
    }
    else if(m.getTopic() == "/odom_topic")
    {
        nav_msgs::Odometry::ConstPtr odom = m.instantiate<nav_msgs::Odometry>();
        if(odom != NULL)
        {
            // 使用odometry数据的代码
            std::cout << "seq: " << odom->header.seq << "\n";
            std::cout << "x_pos: " << odom->pose.pose.position.x << "\n";
            std::cout << "y_pos: " << odom->pose.pose.position.y << "\n";
            std::cout << "z_pos: " << odom->pose.pose.position.z << "\n";
        }
    }

    loop_rate.sleep();
}
bag.close();
