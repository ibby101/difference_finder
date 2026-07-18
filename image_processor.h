#pragma once
#include <string>
#include <vector>
class ImageProcessor {
public:
	static constexpr size_t IMAGE_WIDTH = 540;
	static constexpr size_t IMAGE_HEIGHT = 1200;
	static constexpr size_t EXPECTED_ELEMENTS = IMAGE_HEIGHT * IMAGE_WIDTH;
	static constexpr size_t EXPECTED_BYTES = EXPECTED_ELEMENTS * sizeof(uint16_t);

	static bool validateFile(const std::string& filePath);
	static std::vector<uint16_t> loadRaw(const std::string& filePath);
};

