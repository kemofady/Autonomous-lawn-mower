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
 ```


