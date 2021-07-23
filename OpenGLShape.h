#include "glew/glew.h"
#include "freeglut/glut.h"

#include <WindowsNumerics.h>
using namespace Windows::Foundation::Numerics;


#pragma once
class OpenGLShape
{

public:
	virtual void display() = 0;
	struct VertexXYZColor
	{
		float3 m_Pos;
		float3 m_Color;
	};
    void displayVBOVertexXYZColorAndIndex(
        const int numVertices,
        const GLuint& g_uiVerticesVBO,
        const VertexXYZColor* g_Vertices,
        const int numIndices,
        const GLuint& g_uiIndicesVBO,
        const GLuint* g_Indices
    );

};

