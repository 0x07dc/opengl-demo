#include "OpenGLShape.h"

#include <algorithm>
#include <memory>
#include <vector>

#pragma once
namespace openGLShapes {
    class WaveForm : public OpenGLShape {
    public:
        // If rowLen is not evenly divisible into numVertices, the last (incomplete) row will be truncated
        WaveForm(const int numVertices, const int rowLen);
        ~WaveForm();
        void display() override;

    private:
        double count = 0;
        GLuint g_uiVerticesVBO = 0;
        GLuint g_uiIndicesVBO = 0;
        int numVertices, rowLen;
    };

    class Cube : public OpenGLShape {
    public:
        void display() override;

    private:
        double count = 0;
        float r = 0, g = 0, b = 0;
        GLuint g_uiVerticesVBO = 0;
        GLuint g_uiIndicesVBO = 0;
    };

    class GlutScene : public OpenGLShape {
    public:
        void display() override;

    private:
        double count = 0;
    };
}
