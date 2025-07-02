# 🌿 Autonomous Lawn Mower 🤖

A fully autonomous robotic lawn mower designed for precise and efficient grass cutting using RTK-GPS, IMU, and wheel encoders. This embedded system integrates real-time localization, intelligent decision-making, and robust motor control for seamless operation in outdoor environments.

---


#### 🧠 System Overview

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
        A1[RTK GPS]
        A2[IMU]
        A3[Encoders]
        A4[Rain Sensor]
        A5[LDR (Light Sensor)]
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
    A5 --> B2
    B1 -->|Commands| B2
    B2 --> C1
    C1 --> C2
    C1 --> C3
