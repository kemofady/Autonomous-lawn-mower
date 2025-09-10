# 🌿 Autonomous Lawn Mower 🤖

A fully autonomous robotic lawn mower designed for precise and efficient grass cutting using **RTK-GPS**, **IMU**, and **wheel encoders**. This embedded system integrates real-time localization, intelligent decision-making, and robust motor control for seamless operation in outdoor environments.

---

## 🧠 System Overview

### 📡 Sensors & Localization
- **RTK GPS Module (LC29HDA)**: Provides centimeter-level accuracy for outdoor navigation  
- **IMU (MPU6050)**: Supplies real-time orientation feedback  
- **Wheel Encoders**: Measure wheel rotations for motion estimation

### 🌦️ Environmental Sensors (Handled by Arduino)
- **Rain Sensor**: Detects precipitation to pause mowing for safety  
- **LDR (Light Dependent Resistor)**: Measures ambient light to avoid operation at dusk or night

### 🧾 Decision-Making & Control
- **Raspberry Pi (Ubuntu 22.04)**:
  - Runs ROS 2 Humble (C++ & Python)
  - Processes GPS, IMU, and encoder data
  - Plans navigation paths and coverage areas
  - Sends commands to Arduino over USB
- **Arduino**:
  - Reads environmental sensors (rain, LDR)
  - Handles low-level motor and blade control

---

## 📐 Architecture Diagram

```mermaid
graph TD
    subgraph Sensors
        RTK_GPS(RTK GPS)
        IMU(IMU)
        Encoders(Encoders)
        RainSensor(Rain Sensor)
        LDR(Light Sensor)
    end

    subgraph Controller
        Pi(Raspberry Pi)
        Arduino(Arduino)
    end

    subgraph Actuation
        MotorDrivers(Motor Drivers)
        DriveMotors(Drive Motors)
        BladeMotor(Cutting Blade Motor)
    end

    RTK_GPS --> Pi
    IMU --> Pi
    Encoders --> Pi
    RainSensor --> Arduino
    LDR --> Arduino
    Pi -->|Control Commands via USB| Arduino
    Arduino --> MotorDrivers
    MotorDrivers --> DriveMotors
    MotorDrivers --> BladeMotor

 ```


## 🚀 Setup Instructions

### 🔧 Hardware Requirements
| Component           | Example / Model           |
|---------------------|---------------------------|
| RTK GPS             | Quectel LC29HDA           |
| IMU                 | MPU6050 / BNO055          |
| Encoders            | Quadrature Encoders       |
| Rain Sensor         | Analog Rain Detection Module |
| LDR (Light Sensor)  | Any analog LDR module     |
| Raspberry Pi        | Model 3B+ / 4             |
| Arduino             | UNO / Mega                |
| Motor Drivers       | L298N / BTS7960           |

#### 💻 Software Requirements

- **Ubuntu 22.04** (on Raspberry Pi)
- **Arduino IDE**
- **ROS 2 Humble** (C++ and Python-based nodes)
- **Gazebo Ignition** (simulation environment)
- **pyserial** (for USB serial communication between Raspberry Pi and Arduino)

---

### 🔌 Installation

#### 🚀 Arduino Setup

1. Open `arduino_code/main.ino` in Arduino IDE  
2. Select the correct board and COM port  
3. Upload the sketch

---

#### 🐍 Raspberry Pi Setup (Ubuntu + Python Scripts)

```bash
# On Raspberry Pi with Ubuntu 22.04
sudo apt update
sudo apt install python3-pip
pip3 install pyserial

cd rpi_code/
python3 mower_controller.py
```

#### 🤖 ROS 2 (Humble) Setup

```bash
# Source ROS 2 Humble
source /opt/ros/humble/setup.bash

# Create and build your workspace
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
git clone https://github.com/kemofady/autonomous-lawn-mower.git

cd ~/ros2_ws
rosdep install --from-paths src --ignore-src -r -y
colcon build --symlink-install

# Source the workspace
source install/setup.bash
```
#### 📦 Future Extensions

- ✅ Obstacle avoidance using stereo vision or LiDAR  
- ✅ Full integration with **ROS 2 Humble**  
- ✅ Coverage path planning using boustrophedon or spiral strategies  
- ✅ Mobile app interface for remote monitoring  
- ✅ Enhanced Gazebo Ignition simulation with physical terrain modeling  
- ✅ OTA firmware updates and remote diagnostics

---

### 🤝 Contributing

We welcome all contributions!  
To get started:

```bash
1. Fork this repository
2. Create your feature branch: git checkout -b feature/YourFeature
3. Commit your changes: git commit -m "Add new feature"
4. Push to the branch: git push origin feature/YourFeature
5. Open a Pull Request ✅
```
### 🙌 Maintainer

**Kareem Fady**  
🔗 (https://github.com/kemofady)  
📧 kareemfady111@gmail.com
