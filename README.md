# Dual-Language Robotic Arm Simulation (Python & C++)

A comparative implementation of a 2-Link Robotic Arm simulation using **Inverse Kinematics (IK)**. This project demonstrates the engineering workflow of prototyping complex logic in **Python** before porting to **C++** for real-time performance.

## 🚀 Features
* **Dual Implementation:**
    * **Python (Pygame):** Rapid prototyping of the IK math.
    * **C++ (SFML):** High-performance implementation using strict memory management.
* **Math:** Custom implementation of the **Geometric Inverse Kinematics** algorithm (Law of Cosines).
* **Safety:** Automatic target clamping to prevent mechanical singularities (arm over-extension).

## 🛠️ Tech Stack
* **Languages:** C++17, Python 3.10
* **Libraries:** SFML (C++ Graphics), Pygame (Python Prototyping)
* **Build System:** CMake
* **Tools:** Git, VS Code

## 📐 The Math (Inverse Kinematics)
The core logic calculates joint angles $\theta_1$ and $\theta_2$ based on a target $(x, y)$ using the Law of Cosines:

$$\cos(\theta_2) = \frac{x^2 + y^2 - L_1^2 - L_2^2}{2 L_1 L_2}$$

Where:
* $L_1, L_2$ are the link lengths.
* $(x, y)$ is the target coordinate relative to the base.

## 📦 How to Run
### C++ Version (High Performance)
```bash
cd cpp_impl
mkdir build && cd build
cmake ..
make
./RobotArm
```

### Python Version (Prototype)
```bash
cd python_impl
python3 main.py
```
