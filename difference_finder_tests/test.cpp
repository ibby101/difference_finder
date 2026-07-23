#include "pch.h"
#include "../image_processor.h"

namespace ImageProcessorTests {

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

	// prevents risk of vectors growing to accomodate
	// a number of elements that does not match
	TEST(LoadFile, CorrectInputException) {

		std::string validFile = "test_data/valid_file.raw";

		std::vector<uint16_t> buffer = ImageProcessor::loadRaw(validFile);

		ASSERT_EQ(buffer.size(), ImageProcessor::EXPECTED_ELEMENTS)
			<< "Buffer size doesn't match expected pixel count.\n";
	}

	TEST(QueryThreads, InputZeroCheck) {

		size_t threadCount = 0;

		size_t threadResult = ImageProcessor::queryThreadCount(threadCount);

		ASSERT_EQ(1, threadResult)
			<< "Input: " + std::to_string(threadCount) + " received in thread query, unexpected result output.\n";
	}

	TEST(QueryThreads, InputOneCheck) {

		size_t threadCount = 1;

		size_t threadResult = ImageProcessor::queryThreadCount(threadCount);

		ASSERT_EQ(1, threadResult)
			<< "Input: " + std::to_string(threadCount) + " received in thread query, unexpected result output.\n";
	}

	TEST(QueryThreads, InputNormalCheck) {

		size_t threadCount = 4;

		size_t threadResult = ImageProcessor::queryThreadCount(threadCount);

		ASSERT_EQ(threadCount, threadResult)
			<< "Input: " + std::to_string(threadCount) + " received in thread query, unexpected result output.\n";
	}

	// this test checks the result from a helper function
	// that produces a starting index and count for
	// each worker thread being used in async

	TEST(QueryThreads, FindStartingIndexCheck) {

		size_t elementCount = 10;
		size_t threadCount = 3;
		size_t threadIndex = 0;

		// in this pair, (first) represents the starting index
		// (second) represents the count at which the thread will 
		// finish its task one index before.

		std::pair<size_t, size_t> expectedOutput = {0, 3};

		std::pair<size_t, size_t> helperResult = ImageProcessor::workDistributor(elementCount, threadCount, threadIndex);

		ASSERT_EQ(expectedOutput, helperResult)
			<< "Work distribution function result does not match expected output.\n";
	}

	TEST(ProcessImage, SameSizeCheck) {
		std::vector<uint16_t> smallVector = { 1, 2, 3 };
		std::vector<uint16_t> bigVector = { 1, 2, 3, 4, 5 };

		EXPECT_THROW({
			std::vector<uint16_t> outofBounds = ImageProcessor::calculateDiff(smallVector, bigVector);

			}, std::invalid_argument);
	}

	// testing difference calculation function
	// to ensure that if the same file is provided twice
	// resulting vector will be filled with 0s
	TEST(ProcessImage, IndenticalInputsCheck) {
		std::vector<uint16_t> imageA = { 100, 200, 300 };
		std::vector<uint16_t> imageB = { 100, 200, 300 };

		std::vector<uint16_t> expectedVec = { 0, 0, 0 };

		std::vector<uint16_t> result = ImageProcessor::calculateDiff(imageA, imageB);

		ASSERT_EQ(result, expectedVec)
			<< "output vector does not match expected.\n";
	}

	// ensuring that whichever order the vectors are placed,
	// the result is the same.
	TEST(ProcessImage, SymmetricOutputCheck) {
		std::vector<uint16_t> imageA = { 50, 500, 1000 };
		std::vector<uint16_t> imageB = { 10, 200, 900 };

		EXPECT_EQ(ImageProcessor::calculateDiff(imageA, imageB), ImageProcessor::calculateDiff(imageB, imageA));
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

		std::vector<uint16_t> expectedVec = { 5 };

		std::vector<uint16_t> result = ImageProcessor::calculateDiff(imageA, imageB);

		ASSERT_EQ(result, expectedVec)
			<< "Output vector does not match expected.\n";
	}
	TEST(WriteFile, FileWriteCheck) {
		std::vector<uint16_t> testVector(ImageProcessor::EXPECTED_ELEMENTS);

		bool successfulWrite = ImageProcessor::writeRaw(testVector, "../../outputs/write_file");

		ASSERT_TRUE(successfulWrite)
			<< "Write operation was not successful.\n";
	}

	TEST(WriteFile, WrongSizeCheck) {
		std::vector<uint16_t> smallVector(100);

		EXPECT_FALSE(ImageProcessor::writeRaw(smallVector, "wrong_size_file"));
	}
}






