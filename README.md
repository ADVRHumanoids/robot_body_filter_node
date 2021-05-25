# robot_body_filter_node

# Scope

This node uses the [robot body filter ROS package](http://wiki.ros.org/robot_body_filter) to filter out robot body points of a PointCloud or Laser scan.

# Start

Generate a Catkin workspace:

```
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
git clone https://github.com/peci1/robot_body_filter
git clone https://github.com/ADVRHumanoids/robot_body_filter_node
cd ..
catkin_make
```

# Run

Using XBotCore2.0 and iit-centauro-ros-pkg (branch xbot2-perception) and sourcing the workspace just created:

Open two terminals and run:

``` 
roslaunch xbot2_ws/src/robots/iit-centauro-ros-pkg/centauro_gazebo/launch/centauro_perception.launch
```

``` 
reset && xbot2-core --hw sim -S
``` 

Now it's possible to run the robot filter node using another terminal:
``` 
roslaunch robot_body_filter_node robot_body_filter.launch
``` 

# Result

The first image show the point cloud without filtering:

![Raw_PointCloud](https://github.com/ADVRHumanoids/robot_body_filter_node/blob/main/Img/Raw_PointCloud.png)

The second one with the filter:

![PointCloud_Filtered](https://github.com/ADVRHumanoids/robot_body_filter_node/blob/main/Img/PointCloud_Filtered.png)
