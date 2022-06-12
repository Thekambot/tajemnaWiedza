#include <iostream>
#include "Image.cpp"
#include "ImagePPM.cpp"

namespace stg {

    const std::string INFO_FLAG = "-i";
    const std::string INFO_ALIAS = "--info";
    const std::string ENCRYPT_FLAG = "-e";
    const std::string ENCRYPT_ALIAS = "--encrypt";
    const std::string CHECK_FLAG = "-c";
    const std::string CHECK_ALIAS = "--check";
    const std::string DECRYPT_FLAG = "-d";
    const std::string DECRYPT_ALIAS = "--decrypt";
    const std::string HELP_FLAG = "-h";
    const std::string HELP_ALIAS = "--help";

    const std::string SUPPORTED_EXTENSIONS[] = {".bmp", ".png"};

    bool checkFileExtension(const std::string& fileName) {

        std::string fileExtension = fileName.substr(fileName.find_last_of('.') + 1);

        for (const auto &item : SUPPORTED_EXTENSIONS) {
            if (item == fileExtension)
                return true;
        }

        return false;
    }
}

int main(int argc, char *argv[]) {

//    stg::ImagePPM image = stg::ImagePPM("test.ppm");
//
//    stg::RGB pixel = image.getPixel(3, 0);
//
//    stg::RGB yellow = {255, 255, 0};
//    image.setPixel(0, 0, yellow);
//    image.setPixel(1, 0, yellow);
//    image.setPixel(2, 0, yellow);
//    image.setPixel(3, 0, yellow);
//
//    image.setPixel(0, 2, yellow);
//    image.setPixel(3, 2, yellow);
//
//    image.saveImage("outputTest.ppm");

    std::string flagName = std::string(argv[1]);

    if (flagName == stg::INFO_FLAG || flagName == stg::INFO_ALIAS) {

        std::string filePath = std::string(argv[2]);

        if (!stg::checkFileExtension(filePath))
            return 1;

        stg::ImagePPM image(filePath);
        std::cout << image.getInfo();

    } else if (flagName == stg::HELP_FLAG || flagName == stg::HELP_ALIAS) {

    } else if (flagName == stg::CHECK_FLAG || flagName == stg::CHECK_ALIAS) {

    } else if (flagName == stg::ENCRYPT_FLAG || flagName == stg::ENCRYPT_ALIAS) {

    } else if (flagName == stg::DECRYPT_FLAG || flagName == stg::DECRYPT_ALIAS) {

    }
    return 0;
}
