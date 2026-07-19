#include "pch.h"
#include "../image_processor.h"

TEST(CheckFile, MissingFileException) {

	std::string missingFile = "test_data/fake_file.raw";

	EXPECT_THROW({
		ImageProcessor::validateFile(missingFile);
		}, std::runtime_error);
}
TEST(CheckFile, EmptyFileException) {

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

// risk of vectors growing to accomodate
// a number of elements that does not match
TEST(LoadFile, CorrectInputException) {

	std::string validFile = "test_data/valid_file.raw";

	std::vector<uint16_t> buffer = ImageProcessor::loadRaw(validFile);

	ASSERT_EQ(buffer.size(), ImageProcessor::EXPECTED_ELEMENTS)
		<< "Buffer size doesn't match expected pixel count.\n";
}

// testing difference calculation function
// to ensure that if the same file is provided twice
// resulting vectors will be filled with 0s
TEST(ProcessImage, IndenticalInputsCheck) {
	std::vector<uint16_t> imageA = { 100, 200, 300 };
	std::vector<uint16_t> imageB = { 100, 200, 300 };

	std::vector<uint16_t> expectedVec = { 0, 0, 0 };

	std::vector<uint16_t> result = ImageProcessor::calculateDiff(imageA, imageB);

	ASSERT_EQ(result, expectedVec)
		<< "output vector does not match expected.\n";
}

TEST(ProcessImage, ALargerThanBCheck) {
	std::vector<uint16_t> imageA = { 50, 500, 1000 };
	std::vector<uint16_t> imageB = { 10, 200, 900 };

	std::vector<uint16_t> expectedVec = { 40, 300, 100 };

	std::vector<uint16_t> result = ImageProcessor::calculateDiff(imageA, imageB);

	ASSERT_EQ(result, expectedVec)
		<< "output vector does not match expected.\n";
}

TEST(ProcessImage, BLargerThanACheck) {
	std::vector<uint16_t> imageA = { 5 };
	std::vector<uint16_t> imageB = { 10 };

	std::vector<uint16_t> expectedVec = { 2 };

	std::vector<uint16_t> result = ImageProcessor::calculateDiff(imageA, imageB);

	ASSERT_EQ(result, expectedVec)
		<< "output vector did not match expected.\n";
}





