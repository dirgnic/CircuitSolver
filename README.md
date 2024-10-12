# Circuit Solver Project

This is a **C++ Circuit Solver** application that allows users to graphically construct electrical circuits and calculates the currents and voltages in each branch using Kirchhoff's laws and Gaussian elimination. The program provides an interactive interface where users can define circuit nodes, add resistors and voltage sources, and visualize the results.

## Table of Contents
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [Limitations](#limitations)
- [Future Improvements](#future-improvements)
- [Contributing](#contributing)
- [Acknowledgements](#acknowledgements)

## Features

- **Graphical Interface**: Draw circuit nodes and elements directly on the screen.
- **Interactive Input**: Specify the type of element (resistor or voltage source) and their values.
- **Circuit Analysis**: Calculates currents and voltages using Kirchhoff's laws.
- **Visual Feedback**: Displays calculated currents and voltages on the circuit diagram.
- **Support for Complex Circuits**: Handles circuits with multiple loops and nodes.

## Getting Started

### Prerequisites

To compile and run this project, you need:

- A C++ compiler (e.g., GCC, MinGW, Visual Studio)
- Graphics library compatible with `graphics.h` (e.g., WinBGIm for Windows)

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/dirgnic/CircuitSolver.git
   cd circuit-solver
   ```

2. **Install Graphics Library**

   - **For Windows Users:**

     Download and install [WinBGIm Graphics Library](http://winbgim.codecutter.org/).

     Copy the `graphics.h` and `winbgim.h` files to your compiler's include directory, and the `libbgi.a` file to the lib directory.

   - **For Linux Users:**

     Install the `libgraph` package:

     ```bash
     sudo apt-get install libgraph-dev
     ```

3. **Compile the Program**

   - **On Windows:**

     ```bash
     g++ circuit_solver.cpp -o circuit_solver -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
     ```

   - **On Linux:**

     ```bash
     g++ circuit_solver.cpp -o circuit_solver -lgraph
     ```

## Usage

1. **Run the Executable**

   ```bash
   ./circuit_solver
   ```

2. **Follow the On-Screen Instructions**

   - **Enter the Number of Nodes**

     After starting the program, you will be prompted to enter the number of nodes in your circuit.

   - **Create Nodes**

     Click on the screen to place the nodes. Place as many nodes as you specified.

   - **Add Circuit Elements**

     - **Select Nodes**

       Click on two nodes to select them for adding an element.

     - **Specify Element Type**

       Press:

       - `r` to add a **Resistor**
       - `e` to add a **Voltage Source**
       - Any other key to add a plain wire

     - **Input Element Value**

       For resistors and voltage sources, you will be prompted to enter their values.

   - **Repeat**

     Continue adding elements until your circuit is complete.

3. **Calculate and View Results**

   Once all elements are added, the program will perform the calculations and display the current and voltage for each branch directly on the circuit diagram.

## How It Works

- **Graph Representation**: The circuit is represented as a graph where nodes are junction points and edges are circuit elements.
- **Kirchhoff's Laws**: Applies Kirchhoff's Current Law (KCL) and Kirchhoff's Voltage Law (KVL) to set up equations.
- **Gaussian Elimination**: Solves the system of linear equations derived from KCL and KVL using Gaussian elimination.
- **Visualization**: Uses the graphics library to draw the circuit and display the computed values.

## Limitations

- **Graphics Dependency**: Relies on `graphics.h`, which may not be supported on all platforms.
- **Error Handling**: Limited error checking for user inputs and circuit validity.
- **Component Types**: Only supports resistors and voltage sources.

## Future Improvements

- **Cross-Platform Graphics Support**: Replace `graphics.h` with a more modern and portable graphics library.
- **Additional Components**: Add support for capacitors, inductors, and current sources.
- **User Interface Enhancements**: Improve the GUI for better usability.
- **Error Checking**: Implement robust input validation and error messages.
- **Save and Load Circuits**: Allow users to save their circuits and load them later.

## Contributing

Contributions are welcome! Here's how you can help:

1. **Fork the Repository**

   Click the "Fork" button at the top-right corner of this page.

2. **Clone Your Fork**

   ```bash
   git clone https://github.com/yourusername/circuit-solver.git
   cd circuit-solver
   ```

3. **Create a Branch**

   ```bash
   git checkout -b feature-name
   ```

4. **Make Changes and Commit**

   ```bash
   git add .
   git commit -m "Add new feature"
   ```

5. **Push to Your Fork**

   ```bash
   git push origin feature-name
   ```

6. **Submit a Pull Request**

   Go to the original repository and submit a pull request.

## Acknowledgements

- **WinBGIm Graphics Library**: For providing the graphics functionality.

---

*Feel free to open an issue if you encounter any problems or have suggestions for new features.*
