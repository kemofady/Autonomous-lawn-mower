# bringup_robot2.launch.py
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import LogInfo, ExecuteProcess, DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch.conditions import IfCondition

def generate_launch_description():
    # Launch arguments
    enable_spiral = DeclareLaunchArgument(
        'enable_spiral',
        default_value='true',
        description='Enable spiral motion'
    )

    model_file = os.path.join(get_package_share_directory('model_description'), 'models', 'Assem1.sdf')
    rviz_config_file = os.path.join(get_package_share_directory('model_description'),
                                    'rviz', 'model.rviz')

    return LaunchDescription([
        enable_spiral,
        
        LogInfo(msg='Launching Ignition Gazebo with the model...'),
        
        # Start Ignition Gazebo with the specified model file
        ExecuteProcess(
            cmd=['ign', 'gazebo', '-r', model_file],
            output='screen'
        ),
        
        # Start the ROS-Ignition bridge with remapping for odom
        Node(
            package='ros_ign_bridge',
            executable='parameter_bridge',
            arguments=[
                '/clock@rosgraph_msgs/msg/Clock@ignition.msgs.Clock',
                '/cmd_vel@geometry_msgs/msg/Twist@ignition.msgs.Twist',
                # Remap Ignition odometry to ROS /odom:
                '/model/Assem1/odometry@nav_msgs/msg/Odometry@ignition.msgs.Odometry',
                '/scan@sensor_msgs/msg/LaserScan@ignition.msgs.LaserScan',
                '/imu@sensor_msgs/msg/Imu@ignition.msgs.IMU',
                '/model/Assem1/tf@tf2_msgs/msg/TFMessage@ignition.msgs.Pose_V',
                '/world/car_world/model/Assem1/link/gps_link/sensor/navsat_sensor/navsat@sensor_msgs/msg/NavSatFix@ignition.msgs.NavSat'

            ],
            remappings=[
                ('/model/Assem1/tf', '/tf'),
                ('/model/Assem1/odometry', '/odom'),
                ('/world/car_world/model/Assem1/link/gps_link/sensor/navsat_sensor/navsat' , '/gps')
            ],
            output='screen'
        ),

        # Static transforms
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=['0', '0', '0', '0', '0', '0', 'Assem1/base_link', 'Assem1/lidar'],
            output='screen'
        ),

        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=['0', '0', '0', '0', '0', '0', 'base_link', 'Assem1/base_link'],
            output='screen'
        ),

        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=['0', '0', '0', '0', '0', '0', 'odom', 'base_link'],
            output='screen'
        ),
        
        # Spiral motion node
        Node(
            package='spiral_motion',
            executable='spiral_node',
            name='spiral_motion_node',
            output='screen',
            condition=IfCondition(LaunchConfiguration('enable_spiral'))
        ),
    ])
