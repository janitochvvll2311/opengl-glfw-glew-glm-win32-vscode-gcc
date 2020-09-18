#pragma once
#include "GLEW/glew.h"

class Bmp {

    private:
        unsigned char *m_handle;
        unsigned int width;
        unsigned int height;

    public:
        const unsigned char *Handle() const { return m_handle; }
        unsigned int Width() const { return width; }
        unsigned int Height() const { return height; }

        Bmp(const char *path);
        ~Bmp();

};