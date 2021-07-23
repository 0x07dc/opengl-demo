#include "OpenGLShapes.h"

using namespace openGLShapes;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// WaveForm definitions
//////////////////////////////////////////////////////////////////////////////////////////////////////////
WaveForm::WaveForm(const int numVertices, const int rowLen) :
    numVertices(numVertices), rowLen(rowLen) {
    // Create VBO's
    glGenBuffers(1, &g_uiVerticesVBO);
    glGenBuffers(1, &g_uiIndicesVBO);
}

WaveForm::~WaveForm() {
    glDeleteBuffers(1, &g_uiVerticesVBO);
    glDeleteBuffers(1, &g_uiIndicesVBO);
}

void WaveForm::display() {
    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

    count += 1.0 / 30.0;
    count = fmod(count, 1000000);


    //const int numVertices = 50 * 1000;
    //const int xLen = 10 * 100;
    const int xLen = rowLen;
    const int yLen = numVertices / xLen;
    const float vertSpacingX = 1.0f / (0.15f * xLen);
    const float vertSpacingY = 1.0f / (0.7f * yLen);
    const float offsetX = -((float)xLen * (float)vertSpacingX) / 2.0f;/*-3*/
    const float offsetY = -1;//-1;

    std::unique_ptr<std::vector<VertexXYZColor>> g_Vertices = std::make_unique<std::vector<VertexXYZColor>>(numVertices);// (new VertexXYZColor[numVertices]);
    for (int i = 0; i < numVertices; i++) {
        float adjX = (i % xLen) * vertSpacingX + offsetX;
        float adjY = floor(i / xLen) * vertSpacingY + offsetY;
        float adjZ = -adjY * 3 - 1;
        float waveAdj = sin(count + (float)i / 10.0f) / 10.0f;
        float waveAdj2 = sin(count / 10.1 + (float)i / 10.0f) / 10.0f;
        float waveAdj3 = sin(count + adjY * 20.0f) / 8.0f;
        adjY += (waveAdj + waveAdj2 + waveAdj3) / 2;
        adjX += (waveAdj2 + waveAdj3) / 3;
        adjZ += (waveAdj + waveAdj2) / 100;
        if (i > 40) {
            int temp = 0;
        }
        const double minClamp = 0.0, maxClamp = 1;
        float
            r = abs(waveAdj * 10.0f),
            g = abs(waveAdj2 * 5.0f + waveAdj3 * 5.0f),
            b = abs(waveAdj3 * 10.0f + waveAdj * 10);
        r = (float)std::clamp((double)r, minClamp, maxClamp);
        g = (float)std::clamp((double)g, minClamp, maxClamp);
        b = (float)std::clamp((double)b, minClamp, maxClamp);
        g_Vertices->at(i) = { float3(adjX, adjY, adjZ), float3(r,g,b) };
    }

    // Define the vertex indices for the cube.
    const int numIndices = (xLen - 1) * (yLen - 1) * 4;

    std::unique_ptr<std::vector<GLuint>> g_Indices = std::make_unique<std::vector<GLuint>>(numIndices);// (new GLuint[numIndices]);
    int currentSquare = 0;
    for (int i = 0; i < numIndices / 4; i++) {
        int idx = i * 4;
        // first vertex is i%9, floor(i/9)
        g_Indices->at(idx) = (i % (yLen - 1)) * xLen + floor(i / (yLen - 1));

        // second vertex is firstX+1, firstY
        g_Indices->at(idx + 1) = ((i % (yLen - 1)) + 1) * xLen + floor(i / (yLen - 1));

        // third vertex is firstX+1, firstY+1
        g_Indices->at(idx + 2) = ((i % (yLen - 1)) + 1) * xLen + floor(i / (yLen - 1)) + 1;

        // fourth vertex is firstX, firstY+1
        g_Indices->at(idx + 3) = (i % (yLen - 1)) * xLen + floor(i / (yLen - 1)) + 1;

    }
    displayVBOVertexXYZColorAndIndex(
        numVertices, g_uiVerticesVBO, g_Vertices->data(), numIndices, g_uiIndicesVBO, g_Indices->data()
    );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Cube definitions
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Cube::display() {
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            // Define the 8 vertices of a unit cube
    int xo = 0;// 5;
    int xy = 0;// 2.5;

    const int numVertices = 8;
    VertexXYZColor g_Vertices[numVertices] = {
        { float3(1 + xo,  1 + xy,  1), float3(1, 1, 1) }, // 0
        { float3(-1 + xo,  1 + xy,  1), float3(0, 1, 1) }, // 1
        { float3(-1 + xo, -1 + xy,  1), float3(0, 0, 1) }, // 2
        { float3(1 + xo, -1 + xy,  1), float3(1, 0, 1) }, // 3
        { float3(1 + xo, -1 + xy, -1), float3(1, 0, 0) }, // 4
        { float3(-1 + xo, -1 + xy, -1), float3(0, 0, 0) }, // 5
        { float3(-1 + xo,  1 + xy, -1), float3(0, 1, 0) }, // 6
        { float3(1 + xo,  1 + xy, -1), float3(1, 1, 0) }, // 7
    };

    const int numIndices = 24;
    // Define the vertex indices for the cube.
    GLuint g_Indices[numIndices] = {
        0, 1, 2, 3,                 // Front face
        7, 4, 5, 6,                 // Back face
        6, 5, 2, 1,                 // Left face
        7, 0, 3, 4,                 // Right face
        7, 6, 1, 0,                 // Top face
        3, 2, 5, 4,                 // Bottom face
    };


    displayVBOVertexXYZColorAndIndex(
        numVertices, g_uiVerticesVBO, g_Vertices, numIndices, g_uiIndicesVBO, g_Indices
    );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GlutScene definitions
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlutScene::display() {
    count++;

    //the glTranslatef() routine in the display list alters the position of the next object to be drawn
    glTranslatef(0.0, 0.0, 0.0);
    // set color to object glColor3f(red,green,blue);
    glColor3f(1.0, 0.8, (0.0 + fmod((double)count / 100, 1)));
    // draw a wire tea pot
    glutWireTeapot(1.0);


    // draw a wire sphere
    glTranslatef(-2.5, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glutWireSphere(0.8, 30, 30);

    // draw a wire cone
    glTranslatef(5.0, 0.0, 0.0);
    glColor3f(0.0, 0.6, 1.0);
    glutWireCone(0.8, 1.5, 20, 20);

    // draw a wire cube
    glTranslatef(-1.0, 1.4, 0.0);
    glColor3f(1.0, 0.3, 0.0);
    glutWireCube(1.0);

    // draw a wire torus
    glTranslatef(-3.0, 0.4, 0.0);
    glColor3f(1.0, 0.3, 1.0);
    glutWireTorus(0.2, 0.6, 20, 20);

    // draw a text
    glTranslatef(-2.5, -4.0, 0.0);

    char str[] = { "OpenGL Demo in Visual C++" };

    glColor3f(1.0, 1.0, 1.0);
    // set position to text
    glRasterPos2f(2.0, 0.0);


    for (int i = 0; i < strlen(str); i++)
    {
        // draw each character
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }

    glTranslatef(0.0, 0.0, 0.0);
}
