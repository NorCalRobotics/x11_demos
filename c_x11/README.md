**Starfield Demo by NorCal Robotics**

This is a demo X11 program written in C, designed to showcase a basic graphical application structure and serve as a template for developing more complex X11 applications.

**Copyright (c) 2025 NorCal Robotics - All Rights Reserved.**
**Author:** Gabriel Field

**Build Instructions:**

The project uses a Makefile for compilation. Ensure you have gcc and the X11 development libraries installed on your system. Then, navigate to the project directory in your terminal and run the following command:

```bash
make
```

This will compile the source code and generate the executable named `starfield`.

**Running the Application:**

Once compiled, execute the program using the following command:

```bash
./starfield
```

This will launch a window displaying an animation depicting travel through a starfield.

**Project Structure:**

The project consists of the following files:

- `Makefile`: Defines the build instructions for compiling the C source code.
- `starfield.c`: The main source code file implementing the X11 window creation, graphics drawing, and animation logic.
- `hsv2rgb.c` A source code file containing a utility function for color conversion (HSV to RGB).
- `hsv2rgb.h` A header file containing the declaration for the function defined in `hsv2rgb.c`.
- `README.md` This file.

**Project Purpose:**

This demo serves as a foundational template for building more intricate X11 applications. It demonstrates essential concepts like window creation, event handling, and basic graphics drawing using Xlib functions.

**License:**

This project is licensed under the MIT License. Refer to the [MIT LICENSE](https://opensource.org/licenses/MIT) for details.
