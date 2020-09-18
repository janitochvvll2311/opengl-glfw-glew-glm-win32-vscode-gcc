#include <fstream>
#include "Bmp.hpp"

Bmp::Bmp(const char *path) {
    unsigned char header[54]; 
    unsigned int dataPos;     
    unsigned int imageSize;   

    FILE * file = fopen(path,"rb");
    if (!file) { /*ERROR log pending*/ }

    if ( fread(header, 1, 54, file)!=54 ) { /*ERROR log pending*/ }

    if ( header[0]!='B' || header[1]!='M' ) { /*ERROR log pending*/ }

    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);

    if (imageSize==0)    imageSize=width*height*3; 
    if (dataPos==0)      dataPos=54;

    m_handle = new unsigned char [imageSize];

    fread(m_handle,1,imageSize,file);
    fclose(file);

}

Bmp::~Bmp() {
    delete m_handle;
}