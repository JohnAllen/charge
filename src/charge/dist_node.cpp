

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"
#include <ros/console.h>
#include <lidarLite.h>

int main (int argc, char **argv) {

    ros::init(argc, argv, "dist_node");

    ros::NodeHandle dist_node;
    
    int fd, dist;
    fd = lidar_init(false);

    if (fd == -1) {
        printf("Couldn't initialize the lidar in dist_node.\n");
    }

    std_msgs::Int8 dist_msg;
    ros::Publisher dist_pub = dist_node.advertise<std_msgs::Int8>("dist", 1000);

    ros::Rate r(100);

    while (1==1) {
        // get distance
        dist = lidar_read(fd);
        dist_msg.data = dist;    
        dist_pub.publish(dist_msg);
        ros::spinOnce();
        r.sleep();
    }

    return 0;
}