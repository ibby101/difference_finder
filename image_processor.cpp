#include "image_processor.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>


bool ImageProcessor::validateFile(const std::string& file) {
	std::filesystem::path thisPath(file);

	bool check = std::filesystem::exists(thisPath);

	if (check) {
		std::cout << "The path exists! Yay" << std::endl;
		return true;
	}
	else {
		throw std::runtime_error("File doesn't exist");
	}	
}