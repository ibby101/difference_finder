# difference_finder

## Introduction

The goal of this project is to calculate the pixel difference between two images provided in `.raw` format and output the result in the same `.raw` format. The files contain no metadata or headers to specify data structure. 

Based on the assignment brief, this console-based application was developed using only standard C++ and Visual Studio 2022. No external dependencies (e.g. OpenCV, GUI frameworks) were used to ensure seamless compilation across different machines.

## How to Run the Project

### Running Test Cases

1. Clone the repository or download and extract the source archive, then open the solution in Visual Studio 2022.
2. In the Solution Explorer, right-click **difference_finder_tests** and select **Set as Startup Project**.

![Set Startup Project Tutorial](./tutorial_gifs/startup_project_tut.gif)

3. Run the unit tests via the Test Explorer tab (`Test` > `Test Explorer`).

![Run Test Cases](./tutorial_gifs/running_tests.gif)

### Running from Console

The application requires four command-line arguments (including the executable path).

If the arguments do not match the expected format, the application displays a usage guide explaining the required parameters (two input `.raw` files and an output file name):

<img width="837" height="176" alt="image" src="https://github.com/user-attachments/assets/b39ec70c-2ecb-46c3-ad57-10bfb0e48fec" />

Providing invalid file types or non-`.raw` files will trigger file validation, outputting a clear error message and exiting gracefully:

<img width="1476" height="76" alt="Invalid file type error message" src="https://github.com/user-attachments/assets/3c47590e-e0cc-43b8-ba26-2b7851256ff8" />

Upon successful execution and output generation, a confirmation message is displayed:

<img src="./tutorial_gifs/successful_write.gif" alt="Successful Write" width="1000">

## Declaration of AI Usage

AI was used during this project for guided learning and proofreading documentation. 

## Resources

The following is a list of resources used to understand the required concepts for this project, tools that aided me during the development process, and other features of C++ STL that I've picked up along the way.

- https://boqian.weebly.com/c-programming.html - Bo Qian's C++ Programming Tutorials.
- https://www.eecs.umich.edu/courses/eecs380/HANDOUTS/cppBinaryFileIO-1.html - how to read from a binary file.
- https://www.youtube.com/watch?v=pnoEgNt9B4E - Mike Shah's C++ Tutorials, Read/Write Binary Data in C++, Youtube.
- https://cppreference.com/cpp/filesystem/exists - using filesystem library to perform validation on files.
- https://www.w3schools.com/cpp/ref_fstream_ifstream.asp - fstream for reading raw files.
- https://google.github.io/googletest/primer.html - GoogleTest primer for understanding how to use testing syntax.
- https://www.scs.stanford.edu/05au-cs240c/lab/i386/s02_02.htm - learning about "High Bytes/ Low Bytes" and 16 bits being a "Word".
- https://en.cppreference.com/cpp/filesystem/path/operator_slash - part of `std::filesystem::path`, appends a path segment using the platform's correct separator.
- https://en.cppreference.com/cpp/thread/thread/hardware_concurrency - a useful tool in the `<thread>` library, outputs the number of concurrent threads the active system can support.
- https://www.geeksforgeeks.org/cpp/std-iota-in-cpp/ - std::iota to help fill a vector with values for testing.



