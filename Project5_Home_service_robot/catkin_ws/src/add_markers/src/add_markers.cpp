#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

std::vector<double> robot_pose = {0.0, 0.0};

void get_pose_callback(const nav_msgs::Odometry odom_msg)
{
    robot_pose[0] = odom_msg.pose.pose.position.x;
    robot_pose[1] = odom_msg.pose.pose.position.y;
}

double distance_from_robot_to_point(const std::vector<double> &point)
{
    return std::sqrt(std::pow(point[0] - robot_pose[0], 2) + std::pow(point[1] - robot_pose[1], 2));
}

void set_marker_position(const std::vector<double> &pose, visualization_msgs::Marker &marker)
{
    marker.pose.position.x = pose[0];
    marker.pose.position.y = pose[1];
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
}

enum State
{
    BEFORE_PICKUP,
    IN_TRANSIT,
    DROP_OFF
};

int main(int argc, char **argv)
{

    double pose_distance_tolerance_meters = 0.2;
    std::vector<double> pick_up_zone = {2.5, -1.0};
    std::vector<double> drop_off_zone = {18.0, -4.0};

    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate r(1);

    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    // Subscribe to the odometry to track the pose of the robot
    ros::Subscriber odom_sub = n.subscribe("odom", 10, get_pose_callback);

    // Init the marker
    uint32_t shape = visualization_msgs::Marker::CUBE;
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration(0);

    State state = State::BEFORE_PICKUP;
    while (ros::ok())
    {
        ros::spinOnce();

        // Initially show the marker at the pick-up zone
        if (state == State::BEFORE_PICKUP && distance_from_robot_to_point(pick_up_zone) >= pose_distance_tolerance_meters)
        {
            marker.action = visualization_msgs::Marker::ADD;
            set_marker_position(pick_up_zone, marker);
        }

        // Robot reached the pick-up zone
        if (state == State::BEFORE_PICKUP && distance_from_robot_to_point(pick_up_zone) < pose_distance_tolerance_meters)
        {
            ROS_INFO("Picking up the object");
            marker.action = visualization_msgs::Marker::DELETE;
            marker_pub.publish(marker);
            ros::Duration(5).sleep();
            state = State::IN_TRANSIT;
        }

        // Robot reached the drop-off zone
        if (state == State::IN_TRANSIT && distance_from_robot_to_point(drop_off_zone) < pose_distance_tolerance_meters)
        {
            ROS_INFO("Dropping off the object");
            state = State::DROP_OFF;
            marker.action = visualization_msgs::Marker::ADD;
            set_marker_position(drop_off_zone, marker);
        }

        marker_pub.publish(marker);

        r.sleep();
    }
}