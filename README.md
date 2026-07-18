# difference_finder

## Project Goal

The goal of this project is to be able to produce the difference between two images, which are provided in the ```.raw``` format, and present the output in the same format.

## Initial Thoughts

Considering the conversation I had during the 2nd stage interview with the software engineers, and the emphasis on understanding big endian vs. little endian, my first assumption is that the data has been procured from a system that uses big endian byte sorting. So, when reading the information into my computer, which uses windows 11 on an AMD x86_64 chipset, I will be converting from big endian to little endian.

We can try to read in the raw data without this conversion, and see if it works first, if not, then the assumption is correct.

Based on the assignment requirements, my second assumption is that I am not to use any external libraries, like OpenCV, mainly to avoid compatibility issues when compiled by the assessor, but also to help the project maintain low overhead.

- I will create a GitHub first of all, to document and show my progress as i create this project.
- I must consider how to implement a unit test at each and every stage of the development process.
- I should review each section that has been implemented, and see if it can benefit from async programming.

## Resources

The following is a list of educational resources used to understand the required concepts for this project.

- https://www.eecs.umich.edu/courses/eecs380/HANDOUTS/cppBinaryFileIO-1.html - How to read from a binary file.
- https://www.youtube.com/watch?v=pnoEgNt9B4E - Mike Shah's C++ Tutorials, Read and Write Binary Data in C++, Youtube
