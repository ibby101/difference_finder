#include "pch.h"
#include "../image_processor.h"


TEST(CheckFileExists, MissingFileException) {

	// creating a fake file to check that the program throws a runtime error.

	std::string missingFile = "notTheFile.raw";

	EXPECT_THROW({
		ImageProcessor::validateFile(missingFile);
		}, std::runtime_error);
}