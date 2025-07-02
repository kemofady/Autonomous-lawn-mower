# 🌿 Autonomous Lawn Mower 🤖

A fully autonomous robotic lawn mower designed for precise and efficient grass cutting using RTK-GPS, IMU, and wheel encoders. This embedded system integrates real-time localization, intelligent decision-making, and robust motor control for seamless operation in outdoor environments.

---

## 🧠 System Overview

### 📡 Sensors & Localization
- **RTK GPS Module (LC29HDA)**: Provides centimeter-level positioning
- **IMU (e.g. MPU6050)**: Offers orientation data (roll, pitch, yaw)
- **Wheel Encoders**: Measure distance and wheel rotation for dead reckoning

### 🧾 Decision-Making
- **Raspberry Pi**:
  - Processes sensor data
  - Runs high-level algorithms
  - Sends control commands to Arduino
- **Control Logic**:
  - Navigation
  - Obstacle avoidance
  - Coverage path planning

### ⚙️ Actuation & Control
- **Arduino**:
  - Executes low-level motor control
  - Manages sensor interfacing
- **Motor Drivers**:
  - Drive motors for locomotion and blade actuation

---

## 📐 Architecture Diagram

> Based on your uploaded PDF diagram, here's a clean textual representation:

```mermaid
graph TD
    subgraph Sensors
        A1(RTK GPS)
        A2(IMU)
        A3(Encoders)
        A4(Magnetic Field Sensors)
    end

    subgraph Controller
        B1[Raspberry Pi]
        B2[Arduino]
    end

    subgraph Actuation
        C1[Motor Drivers]
        C2[Drive Motors]
        C3[Cutting Blade Motor]
    end

    A1 --> B1
    A2 --> B1
    A3 --> B1
    A4 --> B2
    B1 -->|Commands| B2
    B2 --> C1
    C1 --> C2
    C1 --> C3
