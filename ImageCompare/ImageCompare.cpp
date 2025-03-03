#include "ImageCompare.h"

ImageCompare::Result ImageCompare::Compare(std::string img1, std::string img2, std::string diffOut)
{
	std::ifstream file1(img1, std::ios::in | std::ios::binary);
	if (!file1.is_open()) return Result();

	BITMAPFILEHEADER bitmapFileHeader1;
	ZeroMemory(&bitmapFileHeader1, sizeof(BITMAPFILEHEADER));
	BITMAPINFOHEADER bitmapInfoHeader1;
	ZeroMemory(&bitmapInfoHeader1, sizeof(BITMAPINFOHEADER));

	file1.read(reinterpret_cast<char *>(&bitmapFileHeader1), sizeof(BITMAPFILEHEADER));
	file1.read(reinterpret_cast<char *>(&bitmapInfoHeader1), sizeof(BITMAPINFOHEADER));

	byte *img1Buffer = new byte[bitmapFileHeader1.bfSize];
	file1.read(reinterpret_cast<char *>(img1Buffer), bitmapFileHeader1.bfSize);

	file1.close();

	std::ifstream file2(img2, std::ios::in | std::ios::binary);
	if (!file2.is_open()) return Result();

	BITMAPFILEHEADER bitmapFileHeader2;
	ZeroMemory(&bitmapFileHeader2, sizeof(BITMAPFILEHEADER));
	BITMAPINFOHEADER bitmapInfoHeader2;
	ZeroMemory(&bitmapInfoHeader2, sizeof(BITMAPINFOHEADER));

	file2.read(reinterpret_cast<char *>(&bitmapFileHeader2), sizeof(BITMAPFILEHEADER));
	file2.read(reinterpret_cast<char *>(&bitmapInfoHeader2), sizeof(BITMAPINFOHEADER));

	byte *img2Buffer = new byte[bitmapFileHeader2.bfSize];
	file2.read(reinterpret_cast<char *>(img2Buffer), bitmapFileHeader2.bfSize);

	file2.close();

	if (bitmapFileHeader1.bfSize != bitmapFileHeader2.bfSize) return Result();

	byte *differenceBuffer = new byte[bitmapFileHeader1.bfSize];

	int samePixels = 0;
	for (int i = 0; i < bitmapFileHeader1.bfSize; i += 3)
	{
		byte diff = 255;
		if (img1Buffer[i + 0] == img2Buffer[i + 0] &&
			img1Buffer[i + 1] == img2Buffer[i + 1] &&
			img1Buffer[i + 2] == img2Buffer[i + 2])
		{
			++samePixels;
			diff = 0;
		}
		differenceBuffer[i + 0] = diff;
		differenceBuffer[i + 1] = diff;
		differenceBuffer[i + 2] = diff;
	}

	Result result;
	result.samePixels = samePixels;
	result.allPixels = bitmapFileHeader1.bfSize / 3;
	result.differentPixels = result.allPixels - result.samePixels;
	result.ratio = static_cast<float>(samePixels) / static_cast<float>(bitmapFileHeader1.bfSize / 3);

	delete[] img1Buffer;
	delete[] img2Buffer;

	std::ofstream file(diffOut, std::ios::out | std::ios::binary);
	file.write(reinterpret_cast<char *>(&bitmapFileHeader1), sizeof(BITMAPFILEHEADER));
	file.write(reinterpret_cast<char *>(&bitmapInfoHeader1), sizeof(BITMAPINFOHEADER));
	file.write(reinterpret_cast<char *>(differenceBuffer), bitmapFileHeader1.bfSize);
	file.close();

	delete[] differenceBuffer;

	return result;
}