#include "pch.h"
#include "../image_processor.h"



// check if the file exists at all

TEST(CheckFile, MissingFileException) {

	// creating a fake file path to check that the program throws a runtime error.

	std::string missingFile = "notTheFile.raw";

	EXPECT_THROW({
		ImageProcessor::validateFile(missingFile);
		}, std::runtime_error);
}

// checking if the file is empty

TEST(CheckFile, EmptyFileException) {

	// path to an actual test file created

	std::string emptyFile = "test_data/empty_file.raw";

	EXPECT_THROW({
		ImageProcessor::validateFile(emptyFile);
		}, std::invalid_argument);
}

// we expect the files that we read to be array of uint16_t
// given that an image is 540x1200, we have a total of 648,000 pixels
// our expected number of bytes is 648,000 pixels * 2 bytes = 1,296,000 bytes

TEST(CheckFile, CorrectFormatException) {

	std::string corruptFile = "test_data/corrupt_file.raw";

	EXPECT_THROW({
		ImageProcessor::validateFile(corruptFile);
		}, std::length_error);
}