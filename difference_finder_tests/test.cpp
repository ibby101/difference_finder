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

TEST(CheckFile, EmptyFileCheck) {

	// path to an actual test file created

	std::string emptyFile = "../proj_contents/test_file.raw";

	EXPECT_THROW({
		ImageProcessor::validateFile(emptyFile);
		}, std::invalid_argument);
}