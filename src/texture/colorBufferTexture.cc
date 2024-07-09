#include "colorBufferTexture.h"

namespace hi{

ColorBufferTexture::ColorBufferTexture(int _width, int _height) 
    : Texture() {
    width = _width;
    height = _height;
    bpp = 3;
    type = Type::TextureColorBuffer;
    generateTexture();
}

void ColorBufferTexture::generateTexture() {
    
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    slot = 0x84C0 + count;
    count ++;
}

}