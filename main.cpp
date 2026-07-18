//#define _CRT_SECURE_NO_WARNINGS
//#include "image_processor.h"
//#include <cstdint>
//#include <algorithm>
//#include <fstream>
//#include <stdlib.h>
//#include <iostream>
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"

int main() {

	//std::vector<uint16_t> buffer = ImageProcessor::loadRaw("C:/Users/Ibroa/source/repos/difference_finder/proj_contents/sino801_540x1200.raw");

	//std::vector<uint16_t> swappedBuffer = buffer;

	//// doing hardware byte-swap on every word element
	//// using MSVC's intrinsic byte swapping feature

	//for (size_t i = 0; i < swappedBuffer.size(); ++i) {
	//	swappedBuffer[i] = _byteswap_ushort(swappedBuffer[i]);
	//}

	//// converting buffer to 8-bit to use in stb write.
	//uint16_t maxVal = *std::max_element(swappedBuffer.begin(), swappedBuffer.end());

	//// creating new vector of single bytes with expected range of values.
	//std::vector<uint8_t> pixels8(ImageProcessor::EXPECTED_ELEMENTS);

	//for (size_t i = 0; i < ImageProcessor::EXPECTED_ELEMENTS; ++i) {
	//	pixels8[i] = maxVal > 0 ? static_cast<uint8_t>((swappedBuffer[i] * 255) / maxVal) : 0;
	//}

	//stbi_write_png("stb_images/swapped_output_801.png", ImageProcessor::IMAGE_WIDTH, ImageProcessor::IMAGE_HEIGHT, 1, pixels8.data(), ImageProcessor::IMAGE_WIDTH);
	//std::cout << "image written to file successfully" << std::endl;

	return 0;
}