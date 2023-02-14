#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <exception>
#include <cassert>

namespace ImageToASCII
{
	const std::vector<std::string> acceptedImageExtensions = { "png", "jpg", "jpeg", "bmp", "gif", "psd", "pdn", "avif", "webp", "svg", "tiff", "heic", "ico", "dds" };

	// Function declarations
	bool assertParameters(int argumentCount, char* arguments[]);
	bool isValidImageFile(const std::string& imageFilePath);
	bool isValidDirectory(const std::string& directoryPath);

	std::string exportASCII(const std::string& imageFilePath, const std::string& directoryPath);

	std::string getErrorLogFileName(const std::string& prefix);
	void writeErrorLog(const std::string& errorMessage, const std::string& imageFilePath, const std::string& directoryPath);

	bool Process(int argc, char* argv[]);
}

