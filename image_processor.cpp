#include "image_processor.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstdint>
#include <thread>



void ImageProcessor::validateFile(const std::string& filePath) {
	std::filesystem::path thisPath(filePath);


	bool check = std::filesystem::exists(thisPath);

	if (!check) {
		/*std::cout << "The path exists! Wonderful." << std::endl;*/
		throw std::runtime_error("\nFile " + filePath + " doesn't exist.\n");
	}

	if (std::filesystem::is_empty(thisPath)) {
		/*std::cout << "This file contains stuff, good." << std::endl;*/
		throw std::invalid_argument("\nFile " + filePath + " has no contents.\n");
	}


	if (std::filesystem::file_size(thisPath) != EXPECTED_BYTES) {
		throw std::length_error("\nThis file size was not expected.\n");
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

	if (imageA.size() != imageB.size()) {
		throw std::invalid_argument("Vector size mismatch detected.\n");
	}
	
	std::vector<uint16_t> output;

	for (size_t i = 0; i < imageA.size(); ++i) {
		//uint16_t difference = imageA[i] - imageB[i]; - used this variable to test underflow
		uint16_t result = std::abs(imageA[i] - imageB[i]);
		output.push_back(result);
	}

	return output;
}

bool ImageProcessor::writeRaw(const std::vector<uint16_t> finalImage, const std::string& outputName) {

	if (finalImage.size() != EXPECTED_ELEMENTS) {
		return false;
	}

	// debug
	//std::filesystem::path cwd = std::filesystem::current_path();
	//std::cout << "Current working directory: " << cwd << std::endl;


	std::filesystem::path outputPath = outputName + ".raw";

	if (outputPath.has_parent_path()) {
		std::filesystem::create_directories(outputPath.parent_path());
	}

	std::ofstream outputFile(outputPath, std::ios::out | std::ios::binary);

	if (!outputFile) {
		return false;
	}

	outputFile.write(reinterpret_cast<const char*>(finalImage.data()), EXPECTED_BYTES);

	return outputFile.good();
}

size_t ImageProcessor::queryThreadCount(const size_t threadCount) {
	 
	size_t output = 0;

	if (threadCount < 2) {
		output = 1;
	}
	else {
		output = threadCount;
	}
	return output;
}

std::pair<size_t, size_t> ImageProcessor::workDistributor(const size_t elementCount, const size_t threadCount, const size_t threadIndex) {

	size_t remainder = elementCount % threadCount;

	size_t dataChunk = elementCount / threadCount;

	size_t startIndex = dataChunk * threadIndex;

	if ((threadCount - 1) == threadIndex) {
		dataChunk += remainder;
	}

	std::pair<size_t, size_t> threadParam = { startIndex, dataChunk };

	return threadParam;
}

void ImageProcessor::parallelDiff(const std::vector<uint16_t>& imageA, const std::vector<uint16_t>& imageB,
		const size_t startIndex, const size_t count, std::vector<uint16_t>& outputVector) {

	size_t lim = startIndex + count;
	for (size_t i = startIndex; i < lim; ++i) {

		uint16_t diff = std::abs(imageA[i] - imageB[i]);

		outputVector[i] = diff;
	}
}

std::vector<uint16_t> ImageProcessor::threadManager(const std::vector<uint16_t>& imageA, const std::vector<uint16_t>& imageB, const size_t threadCount) {

	std::vector<uint16_t> outputVec(imageA.size());

	if (threadCount < 2) {

		outputVec = calculateDiff(imageA, imageB);

		return outputVec;
	}

	std::vector<std::thread> threadIndexes;

	std::pair threadData = { 0,0 };

	for (size_t i = 0; i < threadCount; ++i) {
		threadData = workDistributor(imageA.size(), threadCount, i);
		std::thread t1(parallelDiff, std::ref(imageA), std::ref(imageB), threadData.first, threadData.second, std::ref(outputVec));
		threadIndexes.push_back(std::move(t1));
	}

	for ( auto& thread : threadIndexes) {
		thread.join();
	}

	return outputVec;

}