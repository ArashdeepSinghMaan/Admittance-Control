
# Admittance Control for 2D Plotter

This repository contains the work done for the course project **"Introduction to Medical Robotics"** at **IIT Jodhpur**, focused on implementing admittance control on a 2D plotter system.

---

## 📄 Project Overview

In this project, we built a 2D plotter platform controlled via force-based input using Force Sensing Resistors (FSRs) and joystick control. The goal was to implement admittance control by creating a compliant motion response to external forces. Although the system dynamics were modeled and basic control was achieved, full admittance control could not be implemented due to the inability to achieve torque control with the stepper motors.

---

## 📚 Documentation

To view the complete project documentation, open the file:

> [`Project_report.pdf`](Project_Report.pdf)

This file contains:
- Introduction
- Experimental setup and components
- Implementation details
- Lagrangian dynamics modeling
- Attempted admittance control strategy
- Limitations and conclusion

---

## 🛠️ Code Files

This repository contains three key Arduino codes:

| File Name | Description |
|:---|:---|
| `data_force_sensor_.ino` | Reads and processes Force Sensor data (FSRs). |
| `motor_control_joystick.ino` | Controls the 2D plotter using a joystick for X and Y axis movement. |
| `force_sensor_Control.ino` | Integrates both sensor reading and  control for more advanced movement detection. |

Each file includes appropriate comments for ease of understanding.

---

## 📌 Notes

- Ensure you calibrate the force sensors (FSRs) correctly before running the sensor-based codes.
- Stepper motors are controlled through appropriate drivers interfaced with an Arduino microcontroller.
- **Important**: Full admittance control was not achieved because direct torque control of motors was not possible with the available hardware setup.

---

## 📷 Project Snapshots

Some images of the hardware setup, circuits, and control schematics can be found in the documentation PDF.

---

## 👨‍💻 Team Members

- Arashdeep Singh (M23IRM003)
- Chaitanya Patil (M23IRM004)
- Mayank Kumar (M23IRM007)
- Muskan Suman (M23IRM008)

---

## 📅 Project Timeline

Completed in **April 2025** as part of coursework at **Indian Institute of Technology Jodhpur** under **IDRD Division**.

---

### Video
[![Watch the video](https://img.youtube.com/vi/sHFUjIs1uUQ/maxresdefault.jpg)](https://www.youtube.com/watch?v=sHFUjIs1uUQ&list=PLeGlw_YNKerHX_C80LSZn-a136d4a8ix2)
