#include "MainProcess.h"

#include <chrono>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace ImageToASCII;

bool ImageToASCII::Process(int argc, char* argv[])
{
    bool success = false;

    if (assertParameters(argc, argv))
    {
        std::string imageFilePath = argv[1];
        std::string directoryPath = argv[2];

        try
        {
            // Convert the image to ASCII and export to a text file
            std::string asciiTextFilePath = exportASCII(imageFilePath, directoryPath);
            if (asciiTextFilePath.length() > 0)
            {
                std::cout << "ASCII text file exported successfully to " << asciiTextFilePath << std::endl;

                success = true;
            }
        }
        catch (const std::exception& e)
        {
            std::string errorMessage = "Error: Exception caught: " + std::string(e.what());
            writeErrorLog(errorMessage, imageFilePath, directoryPath);
        }
    }

    return success;
}

bool ImageToASCII::assertParameters(int argumentCount, char* arguments[])
{
    bool success = true;

    if (argumentCount == 3)
    {
        std::string imageFilePath = arguments[1];
        std::string directoryPath = arguments[2];

        // Assert that the image file path is valid
        if (!isValidImageFile(imageFilePath))
        {
            std::string errorMessage = "Error: Invalid image file path.";
            writeErrorLog(errorMessage, imageFilePath, directoryPath);

            success = false;
        }

        // Assert that the directory path is valid
        if (isValidDirectory(directoryPath))
        {
            std::string errorMessage = "Error: Invalid directory path.";
            writeErrorLog(errorMessage, imageFilePath, directoryPath);

            success = false;
        }
    }
    else
    {
        std::cerr << "Error: Invalid number of arguments. The program requires 2 parameters." << std::endl;
        success = false;
    }



    return success;
}

// Function to check if image file is valid
bool ImageToASCII::isValidImageFile(const std::string& imageFilePath)
{
    // List of accepted image file extensions
    std::vector<std::string> acceptedExtensions = { "PNG", "JPG", "JPEG", "BMP", "GIF", "PSD", "PDN", "AVIF", "WebP", "SVG", "TIFF", "HEIC", "ICO", "DDS" };

    // Get file extension from file path
    std::string fileExtension = imageFilePath.substr(imageFilePath.find_last_of(".") + 1);

    // Check if file extension is in the list of accepted extensions
    for (auto& c : fileExtension) c = toupper(c);
    bool match = std::find(acceptedExtensions.begin(), acceptedExtensions.end(), fileExtension) != acceptedExtensions.end();

    return match;
}

// Function to check if directory is valid
bool ImageToASCII::isValidDirectory(const std::string& directoryPath)
{
    // Use C library function to check if directory exists
    FILE* directory;
    fopen_s(&directory, directoryPath.c_str(), "r");

    bool success = (directory != nullptr);

    return success;
}

// Function to export ASCII conversion of image
std::string ImageToASCII::exportASCII(const std::string& imageFilePath, const std::string& directoryPath)
{
    std::string exportPath = "";

    // If directory does not exist, create it
    std::system(("mkdir \"" + directoryPath + "\"").c_str());

    //if (std::system(("mkdir \"" + directoryPath + "\"").c_str()) != 0)
    //{
    //    std::string errorMessage = "Error: Invalid directory path.";
    //    writeErrorLog(errorMessage, imageFilePath, directoryPath);

    //    return exportPath;
    //}

    // Perform ASCII conversion here
    // ...

    exportPath = directoryPath + "Exported ASCII - " + std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) + ".txt";

    // Return export file path
    return exportPath;
}

// Function to get error log file name
std::string ImageToASCII::getErrorLogFileName(const std::string& prefix)
{
    return prefix + std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) + ".csv";
}

void ImageToASCII::writeErrorLog(const std::string& errorMessage, const std::string& imageFilePath, const std::string& directoryPath)
{
    // Get the name of the error log file
    std::string errorLogFileName = getErrorLogFileName("ASCII Error Log - ");

    // Open the error log file
    std::ofstream errorLogFile;
    errorLogFile.open(errorLogFileName);

    // Write the headers to the error log file
    errorLogFile << "Date and Time, Image File Path, Directory Path, Error Message" << std::endl;

    // Get the current date and time
    time_t now = std::time(0);

    tm localTime;
    localtime_s(&localTime, &now);

    // Write the error data to the error log file
    errorLogFile << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "," << imageFilePath << "," << directoryPath << "," << errorMessage << std::endl;

    // Close the error log file
    errorLogFile.close();
}