# difference_finder

## Project Goal

The goal of this project is to be able to produce the difference between two images, which are provided in the ```.raw``` format, and present the output in the same format. There is no metadata or any headers to provide further information about the structure of the information, simple operations can be performed to achieve the result needed.

## How to run project

Clone or download a compressed folder containing the project and open in Visual Studio 2022.

In order to run the test cases, and observe them using the test explorer, set the sub-solution "difference_finder_tests" as the startup project.
![hippo]((https://github.com/user-attachments/assets/abfed499-b6f6-4aa2-9095-a07fd516f470.gif))


## Resources

The following is a list of resources used to understand the required concepts for this project, and other tools that aided me during the development process.

- https://www.eecs.umich.edu/courses/eecs380/HANDOUTS/cppBinaryFileIO-1.html - how to read from a binary file.
- https://www.youtube.com/watch?v=pnoEgNt9B4E - Mike Shah's C++ Tutorials, Read/Write Binary Data in C++, Youtube.
- https://cppreference.com/cpp/filesystem/exists - using filesystem library to perform validation on files
- https://www.w3schools.com/cpp/ref_fstream_ifstream.asp - fstream for reading raw files
- https://google.github.io/googletest/primer.html - GoogleTest primer for understanding how to use testing syntax.
- https://www.scs.stanford.edu/05au-cs240c/lab/i386/s02_02.htm - learning about "High Bytes/ Low Bytes" and 16 bits being a "Word"
- https://en.cppreference.com/cpp/filesystem/path/operator_slash - part of `std::filesystem::path`, appends a path segment using the platform's correct separator.
- https://en.cppreference.com/cpp/thread/thread/hardware_concurrency - a useful tool in the `<thread>` library, outputs the number of concurrent threads the active system can support




