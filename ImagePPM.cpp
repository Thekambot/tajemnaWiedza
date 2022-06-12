#include <iostream>
#include <fstream>
#include <netinet/in.h>
#include <sstream>
#include <vector>
#include "Image.cpp"

#ifndef __IMAGEPPM_CPP__
#define __IMAGEPPM_CPP__

namespace stg {

    class ImagePPM {
    private:
        std::ifstream fileInput;
        long pixelArrayPosition;
        long fileSize;
        bool isBinary;
        std::vector<std::vector<RGB>> pixelArray;

        void loadPixelArray() {
            fileInput.seekg(pixelArrayPosition, std::ios::beg);

            for (int i = 0; i < imageHeight; ++i) {
                stg::RGB rgb{};
                std::vector<RGB> row;

                for (int j = 0; j < imageWidth; ++j) {
                    fileInput >> rgb.R;
                    fileInput >> rgb.G;
                    fileInput >> rgb.B;

                    row.push_back(rgb);
                }

                pixelArray.push_back(row);
            }
        }

    public:

        std::string type;
        int imageWidth;
        int imageHeight;
        int maxColorValue;

        ImagePPM(const std::string &inputFilePath) {
            fileInput = std::ifstream(inputFilePath);

            if (!fileInput.is_open())
                throw std::runtime_error("Could not open file");

            getline(fileInput, type);
            type.erase(type.find_last_not_of(" \n\r\t") + 1);
            fileInput >> imageWidth >> imageHeight;

            if (type == "P1" || type == "P4" || type == "P2" || type == "P5")
                throw std::runtime_error("Only RGB .ppm file is supported");

            if (type == "P3")
                isBinary = false;
            else
                throw std::runtime_error("Binary .ppm is not supported");

            if (type == "P3" || type == "P6")
                fileInput >> maxColorValue;

            pixelArrayPosition = fileInput.tellg();

            fileInput.seekg(0, std::ios::end);
            fileSize = fileInput.tellg();

            loadPixelArray();

            fileInput.seekg(0, std::ios::beg);
        }

        RGB getPixel(long x, long y) {
            return pixelArray[y][x];
        }

        void setPixel(long x, long y, RGB pixel) {
            pixelArray[y][x] = pixel;
        }

        std::string getInfo() {
            std::stringstream info;
            info << ".PPM file\n Width: " + std::to_string(imageWidth)
                    + "\nHeight: " + std::to_string(imageHeight)
                    + "\nFile size: " + std::to_string(fileSize);

            return info.str();
        }

        long getWidth() {
            return imageWidth;
        }

        long getHeight() {
            return imageHeight;
        }

        bool isThereSpaceForMessage(long messageLength) {
            long totalBytes = (imageWidth * imageHeight) * 3;
            long totalBits = messageLength * 8;

            return totalBits >= totalBytes;
        }

        void saveImage(const std::string &outputFilePath) {
            std::ofstream fileOutput(outputFilePath);
            if (!fileOutput.is_open())
                throw std::runtime_error("Could not create file");

            char *buffer = new char[pixelArrayPosition];
            fileInput.read(buffer, pixelArrayPosition);
            fileOutput << buffer;
            free(buffer);

            fileOutput << std::endl;

            for (int i = 0; i < imageHeight; ++i) {
                for (int j = 0; j < imageWidth; ++j) {
                    RGB rgb = pixelArray[i][j];
                    fileOutput << " " + std::to_string(rgb.R) + " ";
                    fileOutput << " " + std::to_string(rgb.G) + " ";
                    fileOutput << " " + std::to_string(rgb.B) + " ";
                }
                fileOutput << std::endl;
            }
        }

        ~ImagePPM() {
            fileInput.close();
        }
    };
}

#endif
