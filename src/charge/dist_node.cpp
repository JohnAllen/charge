#include <ros/ros.h>
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"
#include <ros/console.h>
#include "include/lidarLite.h"
#include <queue>          // std::queue

using namespace std;

bool maxDist(int dist, priority_queue<int> prev_dists)
{
    return 0;
}

void panangleCallback(const std_msgs::Int8 pan_angle_msg)
{
    ROS_INFO("I heard: [%s]", pan_angle_msg);
    PAN_ANGLE = pan_angle_msg.data;
}

int main (int argc, char **argv) {

    ros::init(argc, argv, "dist_node");
    ros::NodeHandle dist_node;
    
    int fd, dist;
    fd = lidar_init(false);

    if (fd == -1)
        printf("Couldn't initialize the lidar in dist_node.\n");

    std_msgs::Int8 dist_msg;
    std_msgs::Int8 max_path_msg;
    ros::Publisher dist_pub = dist_node.advertise<std_msgs::Int8>("dist", 1000);
    ros::Publisher max_path_pub = dist_node.advertise<std_msgs::Int8>("max_path", 1000);
    ros::Subscriber panangle_sub = drive_node.subscribe("pan_angle", 100, panangleCallback);

    ros::Rate r(10);

    int max_path_angle;
    priority_queue<int> prev_dists;
    bool NEW_LONGEST = false;
    while (ros::ok()) {
        // get distance
        dist = lidar_read(fd);
        cout << "distance is " << dist << endl;

        NEW_LONGEST = maxDist(dist, prev_dists);
        if (NEW_LONGEST)
            max_path_msg.data = PAN_ANGLE;    
        max_path_pub.publish();
        
        dist_msg.data = dist;    
        dist_pub.publish(dist_msg);
        ros::spinOnce();
        r.sleep();
    }

    return 0;
}
