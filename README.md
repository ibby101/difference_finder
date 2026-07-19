# difference_finder

## Project Goal

The goal of this project is to be able to produce the difference between two images, which are provided in the ```.raw``` format, and present the output in the same format. There is no metadata or any headers to provide further information about the structure of the information, simple operations can be performed to achieve the result needed.

## Initial Thoughts

Considering the conversation I had during the 2nd stage interview with the software engineers, and the emphasis on understanding big endian vs. little endian, my first assumption is that the data has been procured from a system that uses big endian byte sorting. So, when reading the information into my computer, which uses windows 11 on an AMD x86_64 chipset, I will be converting from big endian to little endian.

We can try to read in the raw data without this conversion, and see if it works first, if not, then the assumption is correct.

Based on the assignment requirements, my second assumption is that I am not to use any external libraries, like OpenCV, mainly to avoid compatibility issues when compiled by the assessor, but also to help the project maintain low overhead.

- I will create a GitHub to document my progress as i create this project.
- I must consider how to implement a unit test at each and every stage of the development process.
- I should review each section that has been implemented, and see if it can be refactored using async programming.

## Resources

The following is a list of resources used to understand the required concepts for this project, and choose the right tools.

- https://www.eecs.umich.edu/courses/eecs380/HANDOUTS/cppBinaryFileIO-1.html - How to read from a binary file.
- https://www.youtube.com/watch?v=pnoEgNt9B4E - Mike Shah's C++ Tutorials, Read/Write Binary Data in C++, Youtube.
- https://cppreference.com/cpp/filesystem/exists - Using filesystem library to perform validation on files
- https://www.w3schools.com/cpp/ref_fstream_ifstream.asp - fstream for reading raw files
- https://google.github.io/googletest/primer.html - GoogleTest primer for understanding how to use testing syntax.
- https://www.scs.stanford.edu/05au-cs240c/lab/i386/s02_02.htm - Learning about "High Bytes/ Low Bytes" and 16 bits being a "Word"

## Bugs and Solutions

When writing test cases for the difference calculation function, I expected that due to the characteristics of the unsigned 16 bit integer data type, doing any subtractions on a smaller number with a larger number would cause an underflow error, as `uint16_t` values cannot go into the negative numbers. However, I have now been made aware of the fact that C++ has a promotion rule, whereby any arithmetic operations carried out on multiple values, the data type will be "promoted" to `int` as anything smaller than this cannot be performed on. This means that we do not have to type-cast the variables or values to (int) before performing a subtraction.

In order to "force" the test case to fail, I performed the difference operation on the elements within the test vectors without the absolute function, equating it to a variable of type `uint16_t`, which would produce a value of 65534. I then fed that variable into an `abs()` bracket which wouldn't actually change anything, as 65534 is already positive, and the underflow had already occured. Doing this test has taught me something i wasn't expecting to learn about how the C++ compiler works under the hood.

<img width="362" height="268" alt="image" src="https://github.com/user-attachments/assets/01aafc35-1584-4558-a4e9-0422dd9732ec" />
