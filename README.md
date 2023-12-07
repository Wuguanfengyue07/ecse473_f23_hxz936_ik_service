# ecse473_f23_hxz936_ik_service
# Introduction
This ROS package implements an ik_service node for testing inverse kinematics solutions. It includes both ik_service and ik_client nodes for handling pose information requests and responses.

# Installation and Running Instructions

Ensure ROS and all related dependencies are installed.

Clone the repository: git clone -https://github.com/Wuguanfengyue07/ecse473_f23_hxz936_ik_service.git

Build the package: Run catkin_make in your catkin workspace

Start ROS core: roscore

Run the service: rosrun ik_service ik_service_node

In another terminal, run the client: rosrun ik_service ik_client_node

# Usage Instructions

The ik_service node receives pose requests and returns processed results. After starting the service, send requests through the ik_client node and observe the responses.

# Functionality Verification
When running the ik_client node, you should see output like the following in the console:

"ik_service node is running."

"ik_service node is ready to receive PoseIK service requests"

"Received a PoseIK service request"

"[number] solutions found"
