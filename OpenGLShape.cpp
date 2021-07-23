#include "OpenGLShape.h"

void OpenGLShape::displayVBOVertexXYZColorAndIndex(
    const int numVertices,
    const GLuint& g_uiVerticesVBO,
    const VertexXYZColor* g_Vertices,
    const int numIndices,
    const GLuint& g_uiIndicesVBO,
    const GLuint* g_Indices
) {

    // Copy the vertex data to the VBO
    glBindBuffer(GL_ARRAY_BUFFER, g_uiVerticesVBO);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(VertexXYZColor), g_Vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Copy the index data to the VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_uiIndicesVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), g_Indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // We need to enable the client stats for the vertex attributes we want 
    // to render even if we are not using client-side vertex arrays.
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Bind the vertices's VBO
    glBindBuffer(GL_ARRAY_BUFFER, g_uiVerticesVBO);
#define MEMBER_OFFSET(s,m) ((char *)NULL + (offsetof(s,m)))
    glVertexPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Pos));
    glColorPointer(3, GL_FLOAT, sizeof(VertexXYZColor), MEMBER_OFFSET(VertexXYZColor, m_Color));

    // Bind the indices's VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_uiIndicesVBO);
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
    glDrawElements(GL_QUADS, numIndices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));


    // Unbind buffers so client-side vertex arrays still work.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // Disable the client side arrays again.
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
};