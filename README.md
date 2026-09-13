# Horizontal Spring-Mass System Simulation

A lightweight, real-time physics simulation of a horizontal spring-mass oscillator built using **C++20** and **SFML 3**. This is my first time developing a physics simulation, created to bridge classroom theoretical equations with interactive desktop graphics.

The system demonstrates simple harmonic motion (SHM) by modeling a block attached horizontally to a fixed wall on a completely frictionless surface.

---

## Features

### 1. Interactive Configuration Panel
Before the graphics window opens, the console acts as an input panel where you can specify structural physical values:
* **Spring Constant (k):** Set the spring stiffness in N/m.
* **Initial Elongation (x):** Set the displacement from equilibrium in meters.
* **Block Mass (m):** Set the inertial mass of the block in kilograms.

### 2. Pre-Simulation Diagnostics
Upon entering data, the program immediately calculates and previews structural properties derived from your parameters:
* Natural and Angular frequencies (ω and f).
* The total duration of one full cycle (Time Period T).
* Total conserved system energy (\(E_{\text{total}}\)), confirming that work done equals kinetic and potential trade-offs.

### 3. Real-Time HUD (Heads-Up Display)
Once the desktop viewport loads, the top and bottom sections continuously calculate and render instantaneous physical metrics:
* **Elapsed Simulation Time** in seconds.
* **Instantaneous Position (x)** relative to the rest baseline.
* **Instantaneous Velocity (v)** tracking direction and scale spikes.
* **Kinetic and Potential Energy (KE & PE)** actively trading values.

### 4. Interactive Snapshot Table
Pressing the **`[SPACE]`** key allows you to record physical readings at any specific millisecond. The values are automatically truncated into clean integers and plotted into a 5-row, 4-column data logging table framed directly below the active animation track.

### 5. Runtime Control Mappings
* `[SPACE]` -> Logs current system metrics into the display grid (up to 5 snapshot benchmarks).
* `[R]`     -> Resets time back to zero and snaps the block to its initial elongation state.
* `[ESC]`   -> Safely updates bounds and kills the rendering context window.

---

## Simulation Video Demo

Below is a brief recording of the simulation window in action, demonstrating the real-time Simple Harmonic Motion calculation, and data snapshot logging to the matrix table.



https://github.com/user-attachments/assets/721cb9a4-675f-4503-870c-5b82b032b683



*(If your platform doesn't support direct video streaming, you can view the raw file directly in the `Assets/simulation-demo.mp4` directory.)*


---

## Underlying Physics & Assumptions

To maintain mathematical accuracy and ensure the simulation is perfectly stable over long periods, the mechanical framework implements the **Analytical Solution** for Simple Harmonic Motion instead of incremental numerical approximations (which drift or artificially gain energy over time).

### Base Equations Used:
* **Angular Frequency:** \(\omega = \sqrt{\frac{k}{m}}\)
* **Position Tracking:** \(x(t) = x_{\text{initial}} \cdot \cos(\omega \cdot t)\)
* **Velocity Tracking:** \(v(t) = -x_{\text{initial}} \cdot \omega \cdot \sin(\omega \cdot t)\)
* **Mechanical Energy Balance:** \(KE = \frac{1}{2}mv^2 \quad \text{and} \quad PE = \frac{1}{2}kx^2\)

### Active Constraints:
1. **Frictionless Environment:** Surface friction, damping forces, and ambient air resistance are neglected.
2. **Ideal Spring Dynamics:** The spring is assumed to be completely massless and obeys Hooke's Law infinitely without plastic deformation.
3. **Rigid Bodies:** The anchor wall has infinite structural mass, and the sliding mass is completely rigid.

---

## File Structure

```text
Spring_Mass/
├── Fonts/
│   └── RobotoMono-MediumItalic.ttf   # UI typography asset file
├── src/
│   └── main.cpp                      # Simulation main control and physics loops
├── CMakeLists.txt                    # Project setup and post-build asset deployment
└── README.md                         # Project documentation
```

---

## Build and Run Instructions

### Prerequisites
* A C++20 compliant compiler (GCC, Clang, or MSVC).
* **SFML 3** graphics libraries installed on your machine ecosystem directory.
* **CMake** (v3.22 or higher).

### Compilation Steps
1. Open the project root workspace directory folder in VS Code or your preferred terminal layout.
2. Run your compiler setup via CMake or execute the build target:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```
3. Run the generated executable directly from your workspace execution path:
   ```bash
   ./Spring-Mass.exe
   ```

*Note: The `CMakeLists.txt` file features a dynamic `POST_BUILD` asset deployment script. This means your font directory is automatically copied into your executable's directory sandbox context every single time you compile, preventing relative path breakages during terminal execution.*
