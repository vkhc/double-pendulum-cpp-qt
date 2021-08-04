# Double pendulum simulation with c++ and Qt6
Double pendulum simulation using modern c++ and Qt6.
![Screenshot 1](https://github.com/vkhc/double-pendulum-cpp-qt/blob/master/screenshots/scr1.PNG)
![Screenshot 2](./screenshots/scr2.png)
![Screenshot 3](./screenshots/scr3.png)

## Numerical solution of ODEs
Semi-implicit Euler method very small time steps (0.15 ms) is used for integration of ODE.
Thus long simulation times won't be accurate. For accurate long term solutions some sympletic
integrator should be implemented.

## Program description
Pendulum is rendered with QPainter, while sliders and checkboxes are used to adjust parameters.
Simulation is interactive and pendulum can be dragged using mouse.
In terms of OOP some refactoring is probably needed.

## How to build
1. Set QT_CONFIG_PATH to lib/cmake directory of Qt in the main CMakeLists.txt
2. Go to build directory
3. Configure cmake by running `cmake ..`
4. Build the project by running `cmake --build .`
5. Copy media folder to the location of executable.

ON WINDOWS: You will probably need to copy Qt DLLs to executable folder as well.
