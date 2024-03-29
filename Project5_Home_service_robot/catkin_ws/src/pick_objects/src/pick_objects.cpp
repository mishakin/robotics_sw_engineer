#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char **argv)
{
    // Initialize the pick_objects node
    ros::init(argc, argv, "pick_objects");

    // tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);

    // Wait 5 sec for move_base action server to come up
    while (!ac.waitForServer(ros::Duration(5.0)))
    {
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    move_base_msgs::MoveBaseGoal goal;

    // set up the frame parameters
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    // Define a position and orientation for the robot to reach
    goal.target_pose.pose.position.x = 2.5;
    goal.target_pose.pose.position.y = -1.0;
    goal.target_pose.pose.orientation.w = 1.0;

    // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending the first goal");
    ac.sendGoal(goal);

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its first goal
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Hooray, the robot reached the first goal");
    else
    {
        ROS_INFO("The failed to reach the first goal");
        return 1;
    }

    // Wait for 5 seconds and go to the next goal
    ros::Duration(5).sleep();

    goal.target_pose.pose.position.x = 18.0;
    goal.target_pose.pose.position.y = -4.0;
    goal.target_pose.pose.orientation.w = 1.0;

    // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending the second goal");
    ac.sendGoal(goal);

    ac.waitForResult();

    // Check if the robot reached its second goal
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Hooray, the robot reached the second goal");
    else
    {
        ROS_INFO("The failed to reach the second goal");
        return 1;
    }

    return 0;
}