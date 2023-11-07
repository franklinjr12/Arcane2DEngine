#pragma once

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include <fstream>
#include <vector>

class Font {
public:
    void stbtt_initfont(void)
    {
        std::fstream infile("assets/16020_FUTURAM.ttf", std::ios::binary | std::ios::in);
        infile.seekg(0, std::ios::end);
        std::streamsize file_size = infile.tellg();
        infile.seekg(0, std::ios::beg);
        font_ttf_buffer = new unsigned char[file_size];
        infile.read((char*)font_ttf_buffer, file_size);
        //std::vector<unsigned char> buffer(file_size);
        //infile.read(reinterpret_cast<char*>(buffer.data()), file_size);
        //memcpy(font_ttf_buffer, buffer.data(), file_size);
        infile.close();
        //fread(font_ttf_buffer, 1, 1 << 20, fopen_s(&file, , "rb"));
        stbtt_BakeFontBitmap(font_ttf_buffer, 0, 32.0, font_temp_bitmap, 512, 512, 32, 96, font_cdata); // no guarantee this fits!
        // can free font_ttf_buffer at this point
        glGenTextures(1, &font_ftex);
        glBindTexture(GL_TEXTURE_2D, font_ftex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, font_temp_bitmap);
        // can free font_temp_bitmap at this point
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    void stbtt_print(float x, float y, char* text)
    {
        // assume orthographic projection with units = screen pixels, origin at top left
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, font_ftex);
        glBegin(GL_QUADS);
        while (*text) {
            if (*text >= 32 && *text < 128) {
                stbtt_aligned_quad q;
                stbtt_GetBakedQuad(font_cdata, 512, 512, *text - 32, &x, &y, &q, 1);//1=opengl & d3d10+,0=d3d9
                glTexCoord2f(q.s0, q.t0); glVertex2f(q.x0, q.y0);
                glTexCoord2f(q.s1, q.t0); glVertex2f(q.x1, q.y0);
                glTexCoord2f(q.s1, q.t1); glVertex2f(q.x1, q.y1);
                glTexCoord2f(q.s0, q.t1); glVertex2f(q.x0, q.y1);
            }
            ++text;
        }
        glEnd();
    }
    unsigned char* font_ttf_buffer;
    unsigned char font_temp_bitmap[512 * 512];
    stbtt_bakedchar font_cdata[96]; // ASCII 32..126 is 95 glyphs
    GLuint font_ftex;
};