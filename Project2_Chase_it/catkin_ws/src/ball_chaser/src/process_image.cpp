#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // Request a service and pass the velocities to it to drive the robot
    ROS_INFO_STREAM("Driving the robot");
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client.call(srv))
        ROS_ERROR("Failed to drive the robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    float angular_velocity_val = 0.5;
    float linear_velocity_val = 0.5;
    float left_border_normed = 0.33F;
    float right_border_normed = 0.66F;

    bool has_white_pixel = false;
    float white_pixel_col_normed = -1.0;

    float ball_projection_row = 0;
    for (int row = 0; row < img.height; ++row)
    {
        for (int byte_idx = 0; byte_idx < img.step; ++byte_idx)
        {
            float col_normed = static_cast<float>(byte_idx) / static_cast<float>(img.step);
            auto brightness = static_cast<int>(img.data[row * img.step + byte_idx]);
            if (brightness == white_pixel)
            {
                has_white_pixel = true;
                white_pixel_col_normed = col_normed;
                break;
            }
        }
        if (has_white_pixel)
            break;
    }

    if (!has_white_pixel || white_pixel_col_normed <= 0.0F || white_pixel_col_normed >= 1.0F)
    {
        drive_robot(0.0F, 0.0F);
        ROS_INFO_STREAM("No white ball was detected, robot stopped.");
    }
    else if (white_pixel_col_normed < left_border_normed)
    {
        drive_robot(0.0F, angular_velocity_val);
        ROS_INFO_STREAM("White ball is to the left, rotating robot to the left");
    }
    else if (white_pixel_col_normed > right_border_normed)
    {
        drive_robot(0.0F, -angular_velocity_val);
        ROS_INFO_STREAM("White ball is to the right, rotating robot to the right");
    }
    else
    {
        drive_robot(linear_velocity_val, 0.0F);
        ROS_INFO_STREAM("White ball is ahead, moving robot forward");
    }
}

int main(int argc, char **argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
