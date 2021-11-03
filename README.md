## Description
A Scheduler library that implements Real-Time Systems schemes.

## Build
You can use CMake GUI or go `mkdir build && cd build && cmake ..` 
You should set `CMAKE_INSTALL_PREFIX` in order to set the install path.

## Install and Run
When you built and installed, the install folder should seem like this:

-- install/
&nbsp;&nbsp; -- application // the executable
&nbsp;&nbsp; -- Scheduler // the library

You can put the example task file or create your own and run `application tasks.txt`
The output will be in `outputStream.txt`
