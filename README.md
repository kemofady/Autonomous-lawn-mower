# 🌿 Autonomous Lawn Mower 🤖

A fully autonomous robotic lawn mower designed for precise and efficient grass cutting using **RTK-GPS**, **IMU**, and **wheel encoders**. This embedded system integrates real-time localization, intelligent decision-making, and robust motor control for seamless operation in outdoor environments.

---

## 🧠 System Overview

### 📡 Sensors & Localization
- **RTK GPS Module (LC29HDA)**: Provides centimeter-level accuracy for outdoor navigation  
- **IMU (e.g. MPU6050)**: Supplies real-time orientation feedback  
- **Wheel Encoders**: Measure wheel rotations for motion estimation

### 🌦️ Environmental Sensors (Handled by Arduino)
- **Rain Sensor**: Detects precipitation to pause mowing for safety  
- **LDR (Light Dependent Resistor)**: Measures ambient light to avoid operation at dusk or night

### 🧾 Decision-Making & Control
- **Raspberry Pi**:
  - Processes GPS, IMU, and encoder data
  - Plans navigation paths and coverage areas
  - Sends commands to Arduino for execution
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
    Pi -->|Control Commands| Arduino
    Arduino --> MotorDrivers
    MotorDrivers --> DriveMotors
    MotorDrivers --> BladeMotor
---

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

### 💻 Software Requirements
- Arduino IDE
- Python 3.9+ (for Raspberry Pi scripts)
- pyserial (for serial communication)
- (Optional) ROS Noetic + Gazebo for simulation and testing

### 🔌 Installation

#### Arduino Setup
1. Open `arduino_code/main.ino` in Arduino IDE
2. Select the correct board and COM port
3. Upload the sketch

#### Raspberry Pi Setup
```bash
# Install dependencies and run controller
sudo apt-get update
sudo apt-get install python3-pip
pip3 install pyserial

cd rpi_code/
python3 mower_controller.py
