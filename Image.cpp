#include <iostream>
#include <fstream>
#include <netinet/in.h>

#ifndef __IMAGE_CPP__
#define __IMAGE_CPP__

namespace stg {
    struct RGB {
        int R, G, B;
    };

    class Image {

    public:
        virtual RGB getPixel(long x, long y);
        virtual void setPixel(long x, long y, RGB pixel);

        virtual std::string getInfo();
        virtual long getWidth();
        virtual long getHeight();

        virtual bool isThereSpaceForMessage(long messageLength);
    };
}

#endif