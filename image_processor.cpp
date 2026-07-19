#include "image_processor.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstdint>



void ImageProcessor::validateFile(const std::string& filePath) {
	std::filesystem::path thisPath(filePath);

	// check variable stores the boolean result of 
	// whether a path to a file exists or not

	bool check = std::filesystem::exists(thisPath);

	if (!check) {
		/*std::cout << "The path exists! Wonderful." << std::endl;*/
		throw std::runtime_error("File " + filePath + " doesn't exist.\n");
	}

	// checking that the actual contents of the file is not empty

	if (std::filesystem::is_empty(thisPath)) {
		/*std::cout << "This file contains stuff, good." << std::endl;*/
		throw std::invalid_argument("File " + filePath + " has no contents.\n");
	}

	// checking that the file is not corrupt, 
	// comparing it against the expected byte size

	if (std::filesystem::file_size(thisPath) != EXPECTED_BYTES) {
		throw std::length_error("This file size was not expected.\n");
	}
}

std::vector<uint16_t> ImageProcessor::loadRaw(const std::string& filePath) {
	validateFile(filePath);

	std::vector<uint16_t> buffer(EXPECTED_ELEMENTS); // expected elements is 648,000 pixels

	std::ifstream file(filePath, std::ios::binary);

	if (!file) {
		throw std::runtime_error("Couldn't open file stream for: " + filePath);
	}

	file.read(reinterpret_cast<char*>(buffer.data()), EXPECTED_BYTES);

	// we use fail() to catch a "short read"
	// which means fewer bytes are available
	// in the file as compared to the requested amount.

	if (file.fail()) {
		throw std::runtime_error("\nStream was corrupted or failed to read all expected bytes.\n");
	}
	return buffer;
}

std::vector<uint16_t> ImageProcessor::calculateDiff(const std::vector<uint16_t>& imageA, const std::vector<uint16_t>& imageB) {
	
	std::vector<uint16_t> output;

	// assuming both vectors are the same size.
	for (int i = 0; i < imageA.size(); ++i) {
		uint16_t result = std::abs(imageA[i] - imageB[i]);
		output.push_back(result);
	}

	return output;
}