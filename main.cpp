//#define _CRT_SECURE_NO_WARNINGS
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
#include "image_processor.h"
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <filesystem>
#include <thread>
#include <iostream>


int main(int argc, char** argv) {

	if (argc != 4) {

		// reducing visual clutter in console
		// by outputting the name of the executable only,
		// instead of the absolute path.

		std::string programName = std::filesystem::path(argv[0]).filename().string();

		std::cerr << "\nExpected Format: " << programName << " <imageA.raw> <imageB.raw> <output_path> \n" << std::endl;
			/*<< "\nNOTE: Please do not add the file suffix at the end, e.g., '.raw', as this will be appended by the program.\n" << std::endl;*/
		return 1;
	}
	
	try {
		std::vector<uint16_t> imageA = ImageProcessor::loadRaw(argv[1]);
		std::vector<uint16_t> imageB = ImageProcessor::loadRaw(argv[2]);

		size_t availableThreads = std::thread::hardware_concurrency();

		size_t threadCount = ImageProcessor::queryThreadCount(availableThreads);

		std::vector<uint16_t> result = ImageProcessor::threadManager(imageA, imageB, threadCount);

		bool success = ImageProcessor::writeRaw(result, argv[3]);

		if (!success) {
			std::cerr << "Failed to write to output file: " << argv[3] << std::endl;
			return 1;
		}
		else {
			std::cout << "\nSucessfully written to output file: " << argv[3] << ".raw \n" << std::endl;
			return 0;
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 1;
}


// old main function that was used to write raw data to .png file to see how they look

/*
int main() {
	std::vector<uint16_t> buffer = ImageProcessor::loadRaw("C:/Users/Ibroa/source/repos/difference_finder/outputs/diff_file.raw");

	std::vector<uint16_t> swappedBuffer = buffer;

	// doing hardware byte-swap on every word element
	// using MSVC's intrinsic byte swapping feature

	for (size_t i = 0; i < swappedBuffer.size(); ++i) {
		swappedBuffer[i] = _byteswap_ushort(swappedBuffer[i]);
	}

	// converting buffer to 8-bit to use in stb write.
	uint16_t maxVal = *std::max_element(buffer.begin(), buffer.end());

	// creating new vector of single bytes with expected range of values.
	std::vector<uint8_t> pixels8(ImageProcessor::EXPECTED_ELEMENTS);

	for (size_t i = 0; i < ImageProcessor::EXPECTED_ELEMENTS; ++i) {
		pixels8[i] = maxVal > 0 ? static_cast<uint8_t>((buffer[i] * 255) / maxVal) : 0;
	}

	stbi_write_png("stb_images/diff_file.png", ImageProcessor::IMAGE_WIDTH, ImageProcessor::IMAGE_HEIGHT, 1, pixels8.data(), ImageProcessor::IMAGE_WIDTH);
	std::cout << "image written to file successfully" << std::endl;
}
*/
