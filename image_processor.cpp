#include "image_processor.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>


bool ImageProcessor::validateFile(const std::string& file) {
	std::filesystem::path thisPath(file);

	// check variable stores the boolean result of 
	// whether a path to a file exists or not

	bool check = std::filesystem::exists(thisPath);

	if (check) {
		std::cout << "The path exists! Wonderful." << std::endl;
	}
	else {
		throw std::runtime_error("File doesn't exist.\n");
	}

	// checking that the actual contents of the file is not empty

	if (!std::filesystem::is_empty(thisPath)) {
		std::cout << "This file contains stuff, good." << std::endl;
	}
	else {
		throw std::invalid_argument("File has no contents.\n");
	}

	// checking that the file is not corrupt, 
	// comparing it against the expected byte size

	const uintmax_t EXPECTED_SIZE = 540 * 1200 * sizeof(uint16_t);

	if (std::filesystem::file_size(thisPath) != EXPECTED_SIZE) {
		throw std::length_error("This file size was not expected.\n");
	}

	return true;

}