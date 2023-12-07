#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ik_service/PoseIK.h"
#include "ur_kinematics/ur_kin.h"

#include <sstream>

// Service function
bool pose_ik(ik_service::PoseIK::Request &req,
ik_service::PoseIK::Response &res)
{
ROS_INFO("Received a PoseIK service request");  

// Get a forward kinematics solution given joint angles.
// Initial joint angles for the arm
double q[] = {3.14, -1.13, 1.51, 3.77, -1.51, 0};
// Variable to receive forward kinematic solution
double T[4][4] = {{0.0, -1.0, 0.0, req.part_pose.position.x}, \
{0.0, 0.0, 1.0, req.part_pose.position.y}, \
{-1.0, 0.0, 0.0 , req.part_pose.position.z}, \
{0.0, 0.0, 0.0, 1.0}};

int num_sol;
// Allocate space for up to eight solutions of six joint angles
double q_sols[8][6];
num_sol = ur_kinematics::inverse(&T[0][0], &q_sols[0][0], 0.0);

res.num_sols = num_sol;  

if (num_sol > 0) {
    ROS_INFO("%i solutions found", num_sol);  

    for (int sol = 0; sol < 8 && sol < num_sol; sol++) {
        for (int ja = 0; ja < 6; ja++) {
            res.joint_solutions[sol].joint_angles[ja] = q_sols[sol][ja];
        }
    }
}
// Forward kinematic solution
//ur_kinematics::forward((double *)&q[0], (double *)&T[0][0]);
//res.num_sols = -1;
return true;
}


/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "ik_service");
  ros::NodeHandle n;

  ROS_INFO("ik_service node is running.");

  // Service node
  ros::ServiceServer service = n.advertiseService("pose_ik", pose_ik);

  ROS_INFO("ik_service node is ready to receive PoseIK service requests");

  ros::spin();
  return 0;
}