<h1 align="center">E6R-1: 3D Printed 6-DOF Robotic Arm</h1>
<div align="center">

*A 6-Degree-of-Freedom robotic arm designed for educational trajectory planning and control, powered by MATLAB/Simulink and ESP32.*

<a href="https://github.com/EARodriguezM/E6R-1/stargazers"><img src="https://img.shields.io/github/stars/EARodriguezM/E6R-1" alt="Stars Badge"/></a> 
<a href="https://github.com/EARodriguezM/E6R-1/network/members"><img src="https://img.shields.io/github/forks/EARodriguezM/E6R-1" alt="Forks Badge"/></a>
<a href="https://github.com/EARodriguezM/E6R-1/pulls"><img src="https://img.shields.io/github/issues-pr/EARodriguezM/E6R-1" alt="Pull Requests Badge"/></a>
<a href="https://github.com/EARodriguezM/E6R-1/issues"><img src="https://img.shields.io/github/issues/EARodriguezM/E6R-1" alt="Issues Badge"/></a>
<a href="https://github.com/EARodriguezM/E6R-1/graphs/contributors"><img alt="GitHub contributors" src="https://img.shields.io/github/contributors/EARodriguezM/E6R-1?color=2b9348"></a>
<a href="https://github.com/EARodriguezM/E6R-1/blob/main/LICENSE"><img src="https://img.shields.io/github/license/EARodriguezM/E6R-1?color=2b9348" alt="License Badge"/></a> 

<a href="https://github.com/EARodriguezM/E6R-1/blob/main/Readme-es.md"><img src="https://img.shields.io/static/v1?label=&labelColor=505050&message=Spanish README &color=%230076D6&style=flat&logo=google-chrome&logoColor=green" alt="website"></a>
</div>

-----

## 📖 Project Overview

The **E6R-1** is a fully printable 6-axis robotic manipulator. It provides a complete development environment for studying robot kinematics, trajectory generation, and embedded control. The system integrates:

  * **Mechanical**: A robust 3D-printed structure designed for standard hobby servos.
  * **Firmware**: Embedded control running on an **ESP32**, interfacing with a **PCA9685** PWM driver.
  * **Software**: A **MATLAB & Simulink** based Digital Twin for simulation, forward/inverse kinematics solving, and direct hardware-in-the-loop (HIL) control.

-----

## 📂 Project Structure

### 1. Hardware (`/1.Hardware`)

Contains the files necessary to build the physical robot:

  * **Printer files**: STL files for 3D printing (e.g., `base v2.stl`, `drivebig v3.stl`, `link_1.stl`).
  * **Components**: Geared towards standard ABS/PLA printing.

### 2. Firmware (`/2.Firmware`)

Contains the source code and Simulink models for the physical robot controller (ESP32):

  * **`Firmware.slx`**: The main Simulink model for the embedded target.
  * **`mainController.mlapp`**: A MATLAB App Designer GUI for controlling the robot.
  * **`libraries/PCA9685`**: C++ drivers for the servo controller.
  * **`kinematics/`**: MATLAB scripts for solving motion (Forward/Inverse).

### 3. Simulation (`/3.Simulation`)

A purely virtual environment to test algorithms before deploying to hardware:

  * **`model.slx`**: The simulation plant model.
  * **`StartupProject.m`**: Script to initialize the path and environment variables.

### 4. Documentation (`/5.Documentation`)

  * **`measures.pdf`**: Physical dimensions and Denavit-Hartenberg (DH) parameters of the arm.

### 5. URDF (`/6.URDF`)

  * Contains the Unified Robot Description Format file (`robot.urdf`) and meshes for visualization in ROS or MATLAB.

-----

## 🚀 Getting Started

### Prerequisites

  * MATLAB & Simulink (Recent version recommended, e.g., R2023b+)
  * Simulink Support Package for Arduino/ESP32
  * 3D Printer (for hardware reproduction)

### Installation & Setup

1.  **Clone the repository**:
    ```bash
    git clone https://github.com/EARodriguezM/E6R-1.git
    ```
2.  **Initialize MATLAB Environment**:
    Open MATLAB, navigate to the `2.Firmware` or `3.Simulation` folder, and run the startup script to add necessary libraries to your path:
    ```matlab
    startup
    % or
    StartupProject
    ```
3.  **Run Simulation**:
    Open `3.Simulation/model.slx` to visualize the robot behavior in a virtual environment.

-----

## 🧮 Kinematics & Control

This project includes custom scripts for calculating the robot's motion.

### Forward Kinematics

Calculate the end-effector position based on joint angles.

```matlab
% Define robot geometry (measures in mm)
robot.a2 = 427;
robot.a3 = 328.5;
robot.d4 = 116.5;
robot.d5 = 116.5;

% Initial configuration matrix (Home position)
gst0 = [1 0 0 robot.d4;
        0 1 0 0;
        0 0 1 robot.a2 + robot.a3 + robot.d5;
        0 0 0 1];

% Input angles in degrees
angles = [60 30 -50 150 20 -100];

% Compute forward kinematics
gst_theta = forwardKinematic(robot, gst0, angles);
disp(gst_theta)
```

### Inverse Kinematics

Calculate required joint angles to reach a specific point in space.

```matlab
% Target configuration matrix
gst_theta = [0.66 -0.71 0.23 223.13;
             0.70  0.48 -0.52 5.70;
             0.26  0.51  0.82 603.6;
             0     0     0    1];

% Compute solutions
solutions = inverseKinematic(robot, gst0, gst_theta);
disp(rad2deg(solutions))
```

### Skew Matrix / Twist Calculation

Helper functions are provided to compute transformation matrices using the Product of Exponentials (PoE) formula.

```matlab
syms a2 a3;
omega = [1; 0; 0];    % Rotation axis
r = [0; 0; a2+a3];
v = cross(r, omega);  % Translation component
xi = [omega; v];      % Twist

T = computeExponential(xi, -0.9961); % Compute T matrix for joint angle q
```

-----

## 🛠 Hardware Architecture

### Electronics

  * **Microcontroller**: ESP32 (DevKit V1 recommended)
  * **Servo Driver**: PCA9685 (I2C 16-channel PWM driver)
  * **Actuators**: Standard Digital Servos (e.g., MG996R for base, lighter servos for wrist)

### Circuit Design

The ESP32 communicates with the PCA9685 via I2C. The `Firmware.slx` model handles the I2C communication and maps trajectory points to PWM signals.

-----

## 📝 Release Notes

**Current Version: 0.0.5**

  * Added MATLAB App Designer GUI (`mainController.mlapp`).
  * Integrated Forward/Inverse kinematics scripts.
  * Updated STL files for `base_rotor` and `connector_straight`.

-----

## 🤝 Contributing

Issues and Pull Requests are welcome!

  * **Issues**: Please use for bug reports or feature requests related to the arm development.
  * **Discussions**: For general chat or troubleshooting help.

-----

*Created by [EARodriguezM](https://github.com/EARodriguezM)*

### Some questions have already been answered in Issues, please read open/closed Issues before asking questions.
