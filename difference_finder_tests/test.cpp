#include "pch.h"
#include "../image_processor.h"

TEST(CheckFile, MissingFileException) {

	// creating a fake file path to check that the program throws a runtime error.

	std::string missingFile = "notTheFile.raw";

	EXPECT_THROW({
		ImageProcessor::validateFile(missingFile);
		}, std::runtime_error);
}
TEST(CheckFile, EmptyFileException) {

	// path to an actual test file created

	std::string emptyFile = "test_data/empty_file.raw";

	EXPECT_THROW({
		ImageProcessor::validateFile(emptyFile);
		}, std::invalid_argument);
}

// expecting the files that we read to be array of uint16_t
// given that an image is 540x1200, we have a total of 648,000 pixels
// our expected number of bytes is 648,000 pixels * 2 bytes = 1,296,000 bytes

TEST(CheckFile, CorrectFormatException) {

	std::string corruptFile = "test_data/corrupt_file.raw";

	EXPECT_THROW({
		ImageProcessor::validateFile(corruptFile);
		}, std::length_error);
}

// since vectors are dynamically allocated,
// there is a risk of them growing to accomodate
// a number of elements that does not match
TEST(LoadFile, CorrectInputException) {

	std::string validFile = "test_data/valid_file.raw";

	std::vector<uint16_t> buffer = ImageProcessor::loadRaw(validFile);

	ASSERT_EQ(buffer.size(), ImageProcessor::EXPECTED_ELEMENTS)
		<< "Buffer size doesn't match expected pixel count.\n";
}

TEST(ProcessImage, IndenticalInputsCheck) {
	std::vector<uint16_t> imageA = { 100, 200, 300 };
	std::vector<uint16_t> imageB = { 100, 200, 300 };

	std::vector<uint16_t> expectedVec = { 0, 0, 0 };

	std::vector<uint16_t> result = ImageProcessor::calculateDiff(imageA, imageB);

	ASSERT_EQ(result, expectedVec)
		<< "Resulting vector does not match expected.\n";
}



