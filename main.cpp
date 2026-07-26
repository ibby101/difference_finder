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

		std::cerr << "\nExpected Format: " << programName << " <imageA.raw> <imageB.raw> <file_name> \n" << std::endl;
		return 1;
	}
	
	try {
		std::vector<uint16_t> imageA = ImageProcessor::loadRaw(argv[1]);
		std::vector<uint16_t> imageB = ImageProcessor::loadRaw(argv[2]);

		// querying device cpu thread capacity	
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